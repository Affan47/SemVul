hydra_recv_nb(int socket, char *buf, int length) {
  int ret = -1;
  char text[64];

  if (hydra_data_ready_timed(socket, (long) waittime, 0) > 0) {
    if ((ret = internal__hydra_recv(socket, buf, length)) <= 0) {
      buf[0] = 0;
      if (debug) {
        sprintf(text, "[DEBUG] RECV [pid:%d]", getpid());
        hydra_dump_data(buf, ret, text);
      }
      return ret;
    }
    if (debug) {
      sprintf(text, "[DEBUG] RECV [pid:%d]", getpid());
      hydra_dump_data(buf, ret, text);

    }
  }
  return ret;
}
