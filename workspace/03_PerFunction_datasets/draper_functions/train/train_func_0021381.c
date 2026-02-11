kvaser_usb_stop_chip(struct kvaser_usb_net_priv *priv)
{
	int err;

	init_completion(&priv->stop_comp);

	err = kvaser_usb_send_simple_msg(priv->dev, CMD_STOP_CHIP,
					 priv->channel);
	if (err)
		return err;

	if (!wait_for_completion_timeout(&priv->stop_comp,
					 msecs_to_jiffies(STOP_TIMEOUT)))
		return -ETIMEDOUT;

	return 0;
}
