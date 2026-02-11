dns_resolve(edge_connection_t *exitconn)
{
  or_circuit_t *oncirc = TO_OR_CIRCUIT(exitconn->on_circuit);
  int is_resolve, r;
  char *hostname = NULL;
  is_resolve = exitconn->_base.purpose == EXIT_PURPOSE_RESOLVE;

  r = dns_resolve_impl(exitconn, is_resolve, oncirc, &hostname);

  switch (r) {
    case 1:


      if (is_resolve) {

        if (hostname)
          send_resolved_hostname_cell(exitconn, hostname);
        else
          send_resolved_cell(exitconn, RESOLVED_TYPE_IPV4);
        exitconn->on_circuit = NULL;
      } else {


        exitconn->next_stream = oncirc->n_streams;
        oncirc->n_streams = exitconn;
      }
      break;
    case 0:


      exitconn->_base.state = EXIT_CONN_STATE_RESOLVING;
      exitconn->next_stream = oncirc->resolving_streams;
      oncirc->resolving_streams = exitconn;
      break;
    case -2:
    case -1:


      if (is_resolve) {
        send_resolved_cell(exitconn,
             (r == -1) ? RESOLVED_TYPE_ERROR : RESOLVED_TYPE_ERROR_TRANSIENT);
      }

      exitconn->on_circuit = NULL;

      dns_cancel_pending_resolve(exitconn->_base.address);

      if (!exitconn->_base.marked_for_close) {
        connection_free(TO_CONN(exitconn));


      }
      break;
    default:
      tor_assert(0);
  }

  tor_free(hostname);
  return r;
}
