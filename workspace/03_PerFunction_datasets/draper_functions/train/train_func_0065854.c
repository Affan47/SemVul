ev_io_start (EV_P_ ev_io *w)
{
  int fd = w->fd;

  if (expect_false (ev_is_active (w)))
    return;

  assert (("libev: ev_io_start called with negative fd", fd >= 0));
  assert (("libev: ev_io_start called with illegal event mask", !(w->events & ~(EV__IOFDSET | EV_READ | EV_WRITE))));

  EV_FREQUENT_CHECK;

  ev_start (EV_A_ (W)w, 1);
  array_needsize (ANFD, anfds, anfdmax, fd + 1, array_init_zero);
  wlist_add (&anfds[fd].head, (WL)w);

  fd_change (EV_A_ fd, w->events & EV__IOFDSET | EV_ANFD_REIFY);
  w->events &= ~EV__IOFDSET;

  EV_FREQUENT_CHECK;
}
