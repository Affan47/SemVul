WorkerProc(int fd)
{
    InitLogger();

    HttpServer* server = new HttpServer();

    server->SetListenSock(fd);
    server->RunServer();

    delete server;
}
