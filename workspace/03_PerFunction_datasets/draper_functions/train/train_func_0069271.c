get_conn(int sock, struct proxied_connection *conns) {
  int index;
  conns = first_conn(conns);

  for(conns; conns->next; conns = conns->next) {
    if(conns->fsock == sock || conns->tsock == sock)
      return conns;
  }

  return NULL;
}
