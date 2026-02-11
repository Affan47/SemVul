set_wait_for_writable_socket(struct connection *pc,
					 bool socket_writable)
{
  static bool previous_state = FALSE;

  fc_assert_ret(pc == &client.conn);

  if (previous_state == socket_writable)
    return;

  log_debug("set_wait_for_writable_socket(%d)", socket_writable);

  g_source_remove(srv_id);
  srv_id = g_io_add_watch(srv_channel,
                          G_IO_IN | (socket_writable ? G_IO_OUT : 0) | G_IO_ERR,
                          get_net_input,
                          NULL);

  previous_state = socket_writable;
}
