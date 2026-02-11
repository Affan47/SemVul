orinoco_hw_allocate_fid(struct orinoco_private *priv)
{
	struct device *dev = priv->dev;
	struct hermes *hw = &priv->hw;
	int err;

	err = hw->ops->allocate(hw, priv->nicbuf_size, &priv->txfid);
	if (err == -EIO && priv->nicbuf_size > TX_NICBUF_SIZE_BUG) {

		priv->nicbuf_size = TX_NICBUF_SIZE_BUG;
		err = hw->ops->allocate(hw, priv->nicbuf_size, &priv->txfid);

		dev_warn(dev, "Firmware ALLOC bug detected "
			 "(old Symbol firmware?). Work around %s\n",
			 err ? "failed!" : "ok.");
	}

	return err;
}
