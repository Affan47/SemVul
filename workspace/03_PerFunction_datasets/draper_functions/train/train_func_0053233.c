dir_watch_parent_changed (GFileMonitor      *monitor,
                          GFile             *file,
                          GFile             *other_file,
                          GFileMonitorEvent  event_type,
                          gpointer           user_data)
{
  DirWatch *watch = user_data;

  g_assert (watch->parent_monitor == monitor);

  if (!g_file_equal (file, watch->directory))
    return;

  if (event_type == G_FILE_MONITOR_EVENT_CREATED)
    {
      if (watch->state)
        return;


      if (dir_exists (file))
        {

          watch->state = TRUE;
          dir_watch_created (watch);
        }
    }
  else if (event_type == G_FILE_MONITOR_EVENT_DELETED)
    {
      if (!watch->state)
        return;

      watch->state = FALSE;
      dir_watch_destroyed (watch);
    }
}
