set_listener_options(struct Listener *listener, int fd)
{
  int is_server;

  is_server = listener_server(listener);


  if (!os_set_sockbufs(fd,
                       is_server ? feature_int(FEAT_SOCKSENDBUF) : CLIENT_TCP_WINDOW,
                       is_server ? feature_int(FEAT_SOCKRECVBUF) : CLIENT_TCP_WINDOW)) {
    report_error(SETBUFS_ERROR_MSG, get_listener_name(listener), errno);
    close(fd);
    return 0;
  }


  if (!os_set_tos(fd,feature_int(is_server ? FEAT_TOS_SERVER : FEAT_TOS_CLIENT))) {
    report_error(TOS_ERROR_MSG, get_listener_name(listener), errno);
  }

  return 1;
}
