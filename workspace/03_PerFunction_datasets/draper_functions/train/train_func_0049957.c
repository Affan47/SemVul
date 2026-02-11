remove_listen_socket(struct ntb_network_listen_socket *listen_socket)
{
        if (listen_socket->source)
                ntb_main_context_remove_source(listen_socket->source);
        ntb_list_remove(&listen_socket->link);
        ntb_close(listen_socket->sock);
        free(listen_socket);
}
