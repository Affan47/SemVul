orinoco_reset(struct work_struct *work)
{
	struct orinoco_private *priv =
		container_of(work, struct orinoco_private, reset_work);
	struct net_device *dev = priv->ndev;
	struct hermes *hw = &priv->hw;
	int err;
	unsigned long flags;

	if (orinoco_lock(priv, &flags) != 0)


		return;

	netif_stop_queue(dev);


	hermes_set_irqmask(hw, 0);
	hermes_write_regn(hw, EVACK, 0xffff);

	priv->hw_unavailable++;
	priv->last_linkstatus = 0xffff;
	netif_carrier_off(dev);

	orinoco_unlock(priv, &flags);


	orinoco_scan_done(priv, true);

	if (priv->hard_reset) {
		err = (*priv->hard_reset)(priv);
		if (err) {
			printk(KERN_ERR "%s: orinoco_reset: Error %d "
			       "performing hard reset\n", dev->name, err);
			goto disable;
		}
	}

	err = orinoco_reinit_firmware(priv);
	if (err) {
		printk(KERN_ERR "%s: orinoco_reset: Error %d re-initializing firmware\n",
		       dev->name, err);
		goto disable;
	}


	orinoco_lock_irq(priv);

	priv->hw_unavailable--;


	if (priv->open && (!priv->hw_unavailable)) {
		err = __orinoco_up(priv);
		if (err) {
			printk(KERN_ERR "%s: orinoco_reset: Error %d reenabling card\n",
			       dev->name, err);
		} else
			dev->trans_start = jiffies;
	}

	orinoco_unlock_irq(priv);

	return;
 disable:
	hermes_set_irqmask(hw, 0);
	netif_device_detach(dev);
	printk(KERN_ERR "%s: Device has been disabled!\n", dev->name);
}
