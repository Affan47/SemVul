handle_control_redirectstream(control_connection_t *conn, uint32_t len,
                              const char *body)
{
  entry_connection_t *ap_conn = NULL;
  char *new_addr = NULL;
  uint16_t new_port = 0;
  smartlist_t *args;
  (void) len;

  args = getargs_helper("REDIRECTSTREAM", conn, body, 2, -1);
  if (!args)
    return 0;

  if (!(ap_conn = get_stream(smartlist_get(args, 0)))
           || !ap_conn->socks_request) {
    connection_printf_to_buf(conn, "552 Unknown stream \"%s\"\r\n",
                             (char*)smartlist_get(args, 0));
  } else {
    int ok = 1;
    if (smartlist_len(args) > 2) {
      new_port = (uint16_t) tor_parse_ulong(smartlist_get(args, 2),
                                            10, 1, 65535, &ok, NULL);
    }
    if (!ok) {
      connection_printf_to_buf(conn, "512 Cannot parse port \"%s\"\r\n",
                               (char*)smartlist_get(args, 2));
    } else {
      new_addr = tor_strdup(smartlist_get(args, 1));
    }
  }

  SMARTLIST_FOREACH(args, char *, cp, tor_free(cp));
  smartlist_free(args);
  if (!new_addr)
    return 0;

  strlcpy(ap_conn->socks_request->address, new_addr,
          sizeof(ap_conn->socks_request->address));
  if (new_port)
    ap_conn->socks_request->port = new_port;
  tor_free(new_addr);
  send_control_done(conn);
  return 0;
}
