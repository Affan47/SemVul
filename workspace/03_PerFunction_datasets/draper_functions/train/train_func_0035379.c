iproc_mdio_probe(struct platform_device *pdev)
{
	struct iproc_mdio_priv *priv;
	struct mii_bus *bus;
	struct resource *res;
	int rc;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->base)) {
		dev_err(&pdev->dev, "failed to ioremap register\n");
		return PTR_ERR(priv->base);
	}

	priv->mii_bus = mdiobus_alloc();
	if (!priv->mii_bus) {
		dev_err(&pdev->dev, "MDIO bus alloc failed\n");
		return -ENOMEM;
	}

	bus = priv->mii_bus;
	bus->priv = priv;
	bus->name = "iProc MDIO bus";
	snprintf(bus->id, MII_BUS_ID_SIZE, "%s-%d", pdev->name, pdev->id);
	bus->parent = &pdev->dev;
	bus->read = iproc_mdio_read;
	bus->write = iproc_mdio_write;

	iproc_mdio_config_clk(priv->base);

	rc = of_mdiobus_register(bus, pdev->dev.of_node);
	if (rc) {
		dev_err(&pdev->dev, "MDIO bus registration failed\n");
		goto err_iproc_mdio;
	}

	platform_set_drvdata(pdev, priv);

	dev_info(&pdev->dev, "Broadcom iProc MDIO bus at 0x%p\n", priv->base);

	return 0;

err_iproc_mdio:
	mdiobus_free(bus);
	return rc;
}
