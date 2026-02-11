set_startup_notification_timeout (GdkDisplay *display,
				  const char *startup_id)
{
  StartupNotificationData *sn_data;

  sn_data = g_new (StartupNotificationData, 1);
  sn_data->display = g_object_ref (display);
  sn_data->startup_id = g_strdup (startup_id);

  g_timeout_add_seconds (EGG_DESKTOP_FILE_SN_TIMEOUT_LENGTH,
			 startup_notification_timeout, sn_data);
}
