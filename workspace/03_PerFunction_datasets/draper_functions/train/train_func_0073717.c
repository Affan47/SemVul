gnome_wp_file_changed (GFileMonitor *monitor,
		       GFile *file,
		       GFile *other_file,
		       GFileMonitorEvent event_type,
		       CcBackgroundXml *data)
{
  gchar *filename;

  switch (event_type) {
  case G_FILE_MONITOR_EVENT_CHANGED:
  case G_FILE_MONITOR_EVENT_CREATED:
    filename = g_file_get_path (file);
    cc_background_xml_load_xml_internal (data, filename, FALSE);
    g_free (filename);
    break;
  default:
    break;
  }
}
