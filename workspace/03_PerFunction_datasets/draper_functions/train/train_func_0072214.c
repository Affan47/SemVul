infy_cb (EV_P_ ev_io *w, int revents)
{
  char buf [EV_INOTIFY_BUFSIZE];
  struct inotify_event *ev = (struct inotify_event *)buf;
  int ofs;
  int len = read (fs_fd, buf, sizeof (buf));

  for (ofs = 0; ofs < len; ofs += sizeof (struct inotify_event) + ev->len)
    infy_wd (EV_A_ ev->wd, ev->wd, ev);
}
