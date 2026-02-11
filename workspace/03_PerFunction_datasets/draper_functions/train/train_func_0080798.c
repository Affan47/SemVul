start_startup_notification (GdkDisplay     *display,
			    EggDesktopFile *desktop_file,
			    const char     *argv0,
			    int             screen,
			    int             workspace,
			    guint32         launch_time)
{
  static int sequence = 0;
  char *startup_id;
  char *description, *wmclass;
  char *screen_str, *workspace_str;

  if (g_key_file_has_key (desktop_file->key_file,
			  EGG_DESKTOP_FILE_GROUP,
			  EGG_DESKTOP_FILE_KEY_STARTUP_NOTIFY,
			  NULL))
    {
      if (!g_key_file_get_boolean (desktop_file->key_file,
				   EGG_DESKTOP_FILE_GROUP,
				   EGG_DESKTOP_FILE_KEY_STARTUP_NOTIFY,
				   NULL))
	return NULL;
      wmclass = NULL;
    }
  else
    {
      wmclass = g_key_file_get_string (desktop_file->key_file,
				       EGG_DESKTOP_FILE_GROUP,
				       EGG_DESKTOP_FILE_KEY_STARTUP_WM_CLASS,
				       NULL);
      if (!wmclass)
	return NULL;
    }

  if (launch_time == (guint32)-1)
    launch_time = gdk_x11_display_get_user_time (display);
  startup_id = g_strdup_printf ("%s-%lu-%s-%s-%d_TIME%lu",
				g_get_prgname (),
				(unsigned long)getpid (),
				g_get_host_name (),
				argv0,
				sequence++,
				(unsigned long)launch_time);

  description = g_strdup_printf (_("Starting %s"), desktop_file->name);
  screen_str = g_strdup_printf ("%d", screen);
  workspace_str = workspace == -1 ? NULL : g_strdup_printf ("%d", workspace);

  gdk_x11_display_broadcast_startup_message (display, "new",
					     "ID", startup_id,
					     "NAME", desktop_file->name,
					     "SCREEN", screen_str,
					     "BIN", argv0,
					     "ICON", desktop_file->icon,
					     "DESKTOP", workspace_str,
					     "DESCRIPTION", description,
					     "WMCLASS", wmclass,
					     NULL);

  g_free (description);
  g_free (wmclass);
  g_free (screen_str);
  g_free (workspace_str);

  return startup_id;
}
