sslErrorComplete(int fdnotused, void *data, size_t sizenotused)
{
    SslStateData *sslState = data;
    assert(sslState != NULL);
    comm_close(sslState->client.fd);
}
