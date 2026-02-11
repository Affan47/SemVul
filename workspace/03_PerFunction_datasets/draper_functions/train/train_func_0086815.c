sread(Sock *sock,char *buf,int buf_size,char *msg)
{
  int ret_val;
  char err_msg[256];
  errno = 0;
  do {
    ret_val = read(sock->socket, buf, buf_size);
  } while (ret_val == -1 && errno == EINTR);
  if (ret_val == 0) {
    FD_CLR(sock->socket, &socket_mask);
    purpose_table[sock->purpose] = NULL;
    close(sock->socket);
    return wait_for_client_read(sock, buf, buf_size, msg);
  }
  if (ret_val == -1) {
    if (msg) {
      sprintf(err_msg, "reading: %s", msg);
      perror(err_msg);
    }
    return -1;
  }
  return ret_val;
}
