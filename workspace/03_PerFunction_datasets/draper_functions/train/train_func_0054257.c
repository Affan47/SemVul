lwpb_transport_socket_client_close(lwpb_transport_t transport)
{
    struct lwpb_transport_socket_client *socket_client =
        (struct lwpb_transport_socket_client *) transport;
    int i;

    if (socket_client->socket == -1)
        return;


    lwpb_transport_free_buf(transport, socket_client->buf);


    close(socket_client->socket);
    socket_client->socket == -1;
}
