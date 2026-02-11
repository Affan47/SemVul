ks8851_remove(struct spi_device *spi)
{
	struct ks8851_net *priv = spi_get_drvdata(spi);

	if (netif_msg_drv(priv))
		dev_info(&spi->dev, "remove\n");

	unregister_netdev(priv->netdev);
	free_irq(spi->irq, priv);
	if (gpio_is_valid(priv->gpio))
		gpio_set_value(priv->gpio, 0);
	regulator_disable(priv->vdd_reg);
	regulator_disable(priv->vdd_io);
	free_netdev(priv->netdev);

	return 0;
}
