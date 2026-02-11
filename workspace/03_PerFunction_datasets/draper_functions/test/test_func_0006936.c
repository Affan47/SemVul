cc770_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	struct cc770_priv *priv = netdev_priv(dev);
	u8 intid;
	int o, n = 0;


	if (priv->can.state == CAN_STATE_STOPPED)
		return IRQ_NONE;

	if (priv->pre_irq)
		priv->pre_irq(priv);

	while (n < CC770_MAX_IRQ) {

		intid = cc770_read_reg(priv, interrupt);
		if (!intid)
			break;
		n++;

		if (intid == 1) {

			if (cc770_status_interrupt(dev))
				break;
		} else {
			o = intid2obj(intid);

			if (o >= CC770_OBJ_MAX) {
				netdev_err(dev, "Unexpected interrupt id %d\n",
					   intid);
				continue;
			}

			if (priv->obj_flags[o] & CC770_OBJ_FLAG_RTR)
				cc770_rtr_interrupt(dev, o);
			else if (priv->obj_flags[o] & CC770_OBJ_FLAG_RX)
				cc770_rx_interrupt(dev, o);
			else
				cc770_tx_interrupt(dev, o);
		}
	}

	if (priv->post_irq)
		priv->post_irq(priv);

	if (n >= CC770_MAX_IRQ)
		netdev_dbg(dev, "%d messages handled in ISR", n);

	return (n) ? IRQ_HANDLED : IRQ_NONE;
}
