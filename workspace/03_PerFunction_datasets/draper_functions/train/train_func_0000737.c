handle_action(struct linked_server *ls,
              const void *data __attr_unused, size_t length __attr_unused)
{
    if (ls->connection->client.reconnecting) {
        uo_server_speak_console(ls->server,
                                "please wait until uoproxy finishes reconnecting");
        return PA_DROP;
    }

    return PA_ACCEPT;
}
