gst_oss4_property_probe_find_device_name_nofd (GstObject * obj,
    const gchar * device_handle, gchar ** device_name)
{
  gboolean res;
  int fd;

  fd = open ("/dev/mixer", O_RDONLY);
  if (fd < 0)
    return FALSE;

  res = gst_oss4_property_probe_find_device_name (obj, fd, device_handle,
      device_name);

  close (fd);
  return res;
}
