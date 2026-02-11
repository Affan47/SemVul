dpy_wait (Display *dpy, struct timeval *timeout) {
  int conn, r;
  fd_set ifds;
  conn = ConnectionNumber (dpy);
  FD_ZERO (&ifds);
  FD_SET (conn, &ifds);
  X_CALL(r = select (conn+1, &ifds, NULL, NULL, timeout));
  return (r > 0) && FD_ISSET (conn, &ifds);
}
