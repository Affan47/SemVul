gst_rtp_channels_get_by_index (gint channels, guint idx)
{
  gint i;
  const GstRTPChannelOrder *res = NULL;

  for (i = 0; channel_orders[i].pos; i++) {
    if (channel_orders[i].channels != channels)
      continue;

    if (idx == 0) {
      res = &channel_orders[i];
      break;
    }
    idx--;
  }
  return res;
}
