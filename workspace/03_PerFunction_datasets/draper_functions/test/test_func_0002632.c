ap_stream_wants_exit_attention(connection_t *conn)
{
  entry_connection_t *entry;
  if (conn->type != CONN_TYPE_AP)
    return 0;
  entry = TO_ENTRY_CONN(conn);

  if (conn->state == AP_CONN_STATE_CIRCUIT_WAIT &&
      !conn->marked_for_close &&
      !(entry->want_onehop) &&
      !(entry->use_begindir) &&
      !(entry->chosen_exit_name) &&
      !connection_edge_is_rendezvous_stream(TO_EDGE_CONN(conn)) &&
      !circuit_stream_is_being_handled(TO_ENTRY_CONN(conn), 0,
                                       MIN_CIRCUITS_HANDLING_STREAM))
    return 1;
  return 0;
}
