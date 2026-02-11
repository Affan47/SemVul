network_check_listeners(List *listeners,fd_set *fds) {
  struct network_info n;
  if (listeners == NULL) return;
  n.rfds = fds;
  n.wfds = NULL;
  list_foreach(listeners,network_check_listener,&n);
}
