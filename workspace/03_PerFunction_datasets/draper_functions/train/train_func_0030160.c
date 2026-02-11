network_connection_do_recv(Network_connection *con, void *data,size_t len) {
  int ret;

  ret = recv(con->fd,data,len,MSG_DONTWAIT);
  if (ret < 0 && errno == EAGAIN) {
    return 0;
  }
  if (ret <= 0) {
    if (ret < 0)
      NETDEBUG("Network error on fd %d -> %s",con->fd,strerror(errno));
    else
      NETDEBUG("Connection to fd %d closed",con->fd);
    close(con->fd);
    con->fd = -1;
    return -1;
  }
  return ret;
}
