rp5c01_rtc_probe(struct platform_device *dev)
{
	struct resource *res;
	struct rp5c01_priv *priv;
	struct rtc_device *rtc;
	int error;

	res = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;

	priv = devm_kzalloc(&dev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->regs = devm_ioremap(&dev->dev, res->start, resource_size(res));
	if (!priv->regs)
		return -ENOMEM;

	sysfs_bin_attr_init(&priv->nvram_attr);
	priv->nvram_attr.attr.name = "nvram";
	priv->nvram_attr.attr.mode = S_IRUGO | S_IWUSR;
	priv->nvram_attr.read = rp5c01_nvram_read;
	priv->nvram_attr.write = rp5c01_nvram_write;
	priv->nvram_attr.size = RP5C01_MODE;

	spin_lock_init(&priv->lock);

	platform_set_drvdata(dev, priv);

	rtc = devm_rtc_device_register(&dev->dev, "rtc-rp5c01", &rp5c01_rtc_ops,
				  THIS_MODULE);
	if (IS_ERR(rtc))
		return PTR_ERR(rtc);
	priv->rtc = rtc;

	error = sysfs_create_bin_file(&dev->dev.kobj, &priv->nvram_attr);
	if (error)
		return error;

	return 0;
}
