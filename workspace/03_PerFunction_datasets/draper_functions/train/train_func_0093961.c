trash_watcher_unwatch (TrashWatcher *watcher)
{
  TrashMount *mount;

  g_assert (watcher->watching);

  if (watcher->homedir_type != TRASH_WATCHER_NO_WATCH)
    trash_dir_unwatch (watcher->homedir_trashdir);

  for (mount = watcher->mounts; mount; mount = mount->next)
    if (mount->type != TRASH_WATCHER_NO_WATCH)
      {
        trash_dir_unwatch (mount->dirs[0]);
        trash_dir_unwatch (mount->dirs[1]);
      }

  watcher->watching = FALSE;
}
