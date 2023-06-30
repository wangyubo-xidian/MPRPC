#include <iostream>

#include "mprpcapplication.h"
#include "user.pb.h"
#include "mprpcchannel.h"

int main(int argc, char** argv)
{
    // 整个程序启动之后，使用mprpc框架来享受rpc服务调用，一定需要先调用框架的初始化函数（只初始化一次）
    MprpcApplication::Init(argc, argv);

    // 演示调用远程发布的rpc方法Login
    fixbug::UserServiceRpc_Stub stub(new MprpcChannel());
    
    // rpc方法的请求参数
    fixbug::LoginRequest request;
    request.set_name("zhang san");
    request.set_pwd("123456");

    // rpc方法的响应
    fixbug::LoginResponse response;

    // 发起rpc方法的调用，同步的rpc调用过程 MprpcChannel::callMethod
    // RpcChannel -> RpcChannel::callMethod 集中来做所有Rpc方法调用的参数序列化和网络发送
    stub.Login(nullptr, &request, &response, nullptr);

    // 一次调用rpc调用完成，读调用的结果
    if (response.result().errcode() == 0)
    {
        std::cout << "rpc login response success:" << response.success() << std::endl;
    }
    else
    {
        std::cout << "rpc login response error:" << response.result().errmsg() << std::endl;
    }

    // 演示调用远程发布的rpc方法Register
    fixbug::RegisterRequest req;
    req.set_id(2000);
    req.set_name("mprpc");
    req.set_pwd("666666");

    fixbug::RegisterResponse rsp;
    
    // 以同步的方式发起rpc调用请求，等待返回结果
    stub.Register(nullptr, &req, &rsp, nullptr);

    // 一次调用rpc调用完成，读调用的结果
    if (rsp.result().errcode() == 0)
    {
        std::cout << "rpc register response success:" << rsp.success() << std::endl;
    }
    else
    {
        std::cout << "rpc register response error:" << rsp.result().errmsg() << std::endl;
    }

    return 0;
}