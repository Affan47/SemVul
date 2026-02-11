lbs_start_mesh(struct lbs_private *priv)
{
	lbs_add_mesh(priv);

	if (device_create_file(&priv->dev->dev, &dev_attr_lbs_mesh))
		netdev_err(priv->dev, "cannot register lbs_mesh attribute\n");
}
