connection_state_is_connecting(connection_t *conn)
{
  tor_assert(conn);

  if (conn->marked_for_close)
    return 0;
  switch (conn->type)
    {
    case CONN_TYPE_OR:
      return conn->state == OR_CONN_STATE_CONNECTING;
    case CONN_TYPE_EXIT:
      return conn->state == EXIT_CONN_STATE_CONNECTING;
    case CONN_TYPE_DIR:
      return conn->state == DIR_CONN_STATE_CONNECTING;
    }

  return 0;
}
