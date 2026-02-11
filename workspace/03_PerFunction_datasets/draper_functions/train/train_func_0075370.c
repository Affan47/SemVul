tpmfront_probe(struct xenbus_device *dev,
		const struct xenbus_device_id *id)
{
	struct tpm_private *priv;
	struct tpm_chip *chip;
	int rv;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv) {
		xenbus_dev_fatal(dev, -ENOMEM, "allocating priv structure");
		return -ENOMEM;
	}

	rv = setup_chip(&dev->dev, priv);
	if (rv) {
		kfree(priv);
		return rv;
	}

	rv = setup_ring(dev, priv);
	if (rv) {
		chip = dev_get_drvdata(&dev->dev);
		ring_free(priv);
		return rv;
	}

	tpm_get_timeouts(priv->chip);

	return tpm_chip_register(priv->chip);
}
