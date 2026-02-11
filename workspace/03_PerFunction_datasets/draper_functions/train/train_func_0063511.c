network_add_listeners(List *listeners,fd_set *fds,int *maxfd) {
  struct network_info n;
  if (listeners == NULL) return;
  n.rfds = fds;
  n.wfds = NULL;
  n.maxfd = *maxfd;
  list_foreach(listeners,network_do_add_listeners,&n);
  *maxfd = n.maxfd;
}
