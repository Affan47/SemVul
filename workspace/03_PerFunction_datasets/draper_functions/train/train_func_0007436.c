ev_handler(struct mg_connection *conn, enum mg_event ev) {
  if (ev == MG_REQUEST) {
    return send_reply(conn);
  } else if (ev == MG_AUTH) {
    return MG_TRUE;
  } else {
    return MG_FALSE;
  }
}
