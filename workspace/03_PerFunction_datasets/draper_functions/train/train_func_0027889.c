update_poll_flags(struct ntb_connection *conn)
{
        enum ntb_main_context_poll_flags flags = NTB_MAIN_CONTEXT_POLL_IN;

        if (connection_is_ready_to_write(conn))
                flags |= NTB_MAIN_CONTEXT_POLL_OUT;

        ntb_main_context_modify_poll(conn->socket_source, flags);
}
