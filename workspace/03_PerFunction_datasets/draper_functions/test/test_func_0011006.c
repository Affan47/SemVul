find_file_monitor (GFileMonitor *monitor,
                   GFile        *file)
{
  GFile *monitored_file;

  monitored_file = g_object_get_qdata (G_OBJECT (monitor), garcon_menu_file_quark);

  if (monitored_file != NULL && g_file_equal (monitored_file, file))
    return 0;
  else
    return -1;
}
