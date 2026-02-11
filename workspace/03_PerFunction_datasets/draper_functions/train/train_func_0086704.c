gst_mpd_client_get_availability_start_time (GstMpdClient * client)
{
  GstDateTime *t;

  g_return_val_if_fail (client != NULL, NULL);

  GST_MPD_CLIENT_LOCK (client);
  t = client->mpd_node->availabilityStartTime;
  GST_MPD_CLIENT_UNLOCK (client);
  return t;
}
