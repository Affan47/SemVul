gst_color_balance_channel_dispose (GObject * object)
{
  GstColorBalanceChannel *channel = GST_COLOR_BALANCE_CHANNEL (object);

  if (channel->label)
    g_free (channel->label);

  channel->label = NULL;

  if (parent_class->dispose)
    parent_class->dispose (object);
}
