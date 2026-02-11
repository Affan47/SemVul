stop_server()
{
    if (rc_socket != 0)
        rc_socket->close();

    if (rc_server.isListening())
        rc_server.close();

}
