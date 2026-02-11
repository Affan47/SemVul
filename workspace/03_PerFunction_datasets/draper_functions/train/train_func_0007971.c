managesServer(const Server &server)
{
    return server.nativeUrl().startsWith("file://");
}
