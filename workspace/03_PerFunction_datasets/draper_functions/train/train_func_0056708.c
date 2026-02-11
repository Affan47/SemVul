do_inotify_rm_watch (int wd)
{
  NEED_INOTIFY (-1);

  if (inotify_rm_watch (inotify_fd, wd) == -1) {
    reply_with_perror ("%d", wd);
    return -1;
  }

  return 0;
}
