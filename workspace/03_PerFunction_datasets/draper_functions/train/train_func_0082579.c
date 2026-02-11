gst_festival_close (GstFestival * festival)
{
  if (festival->info == NULL)
    return;

  if (festival->info->server_fd != -1)
    close (festival->info->server_fd);
  GST_OBJECT_FLAG_UNSET (festival, GST_FESTIVAL_OPEN);
  return;
}
