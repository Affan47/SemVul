get_im_channel (PhoneyImChannelFactory *self,
		TpHandle handle,
		gboolean *created)
{
	PhoneyImChannelFactoryPrivate *priv =
		PHONEY_IM_CHANNEL_FACTORY_GET_PRIVATE (self);
	PhoneyIMChannel *chan =
		g_hash_table_lookup (priv->channels, GUINT_TO_POINTER (handle));

	if (chan)
	{
		if (created)
			*created = FALSE;
	}
	else
	{
		chan = new_im_channel (self, handle);
		if (created)
			*created = TRUE;
	}
	g_assert (chan);
	return chan;
}
