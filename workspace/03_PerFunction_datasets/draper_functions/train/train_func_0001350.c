wsm_channel_switch_indication(struct cw1200_common *priv,
					 struct wsm_buf *buf)
{
	WARN_ON(WSM_GET32(buf));

	priv->channel_switch_in_progress = 0;
	wake_up(&priv->channel_switch_done);

	wsm_unlock_tx(priv);

	return 0;

underflow:
	return -EINVAL;
}
