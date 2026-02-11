thunder_i2c_probe_pci(struct pci_dev *pdev,
				 const struct pci_device_id *ent)
{
	struct device *dev = &pdev->dev;
	struct octeon_i2c *i2c;
	int ret;

	i2c = devm_kzalloc(dev, sizeof(*i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	i2c->roff.sw_twsi = 0x1000;
	i2c->roff.twsi_int = 0x1010;
	i2c->roff.sw_twsi_ext = 0x1018;

	i2c->dev = dev;
	pci_set_drvdata(pdev, i2c);
	ret = pcim_enable_device(pdev);
	if (ret)
		return ret;

	ret = pci_request_regions(pdev, DRV_NAME);
	if (ret)
		return ret;

	i2c->twsi_base = pcim_iomap(pdev, 0, pci_resource_len(pdev, 0));
	if (!i2c->twsi_base)
		return -EINVAL;

	thunder_i2c_clock_enable(dev, i2c);
	ret = device_property_read_u32(dev, "clock-frequency", &i2c->twsi_freq);
	if (ret)
		i2c->twsi_freq = 100000;

	init_waitqueue_head(&i2c->queue);

	i2c->int_enable = thunder_i2c_int_enable;
	i2c->int_disable = thunder_i2c_int_disable;
	i2c->hlc_int_enable = thunder_i2c_hlc_int_enable;
	i2c->hlc_int_disable = thunder_i2c_hlc_int_disable;

	ret = pci_enable_msix(pdev, &i2c->i2c_msix, 1);
	if (ret)
		goto error;

	ret = devm_request_irq(dev, i2c->i2c_msix.vector, octeon_i2c_isr, 0,
			       DRV_NAME, i2c);
	if (ret)
		goto error;

	ret = octeon_i2c_init_lowlevel(i2c);
	if (ret)
		goto error;

	octeon_i2c_set_clock(i2c);

	i2c->adap = thunderx_i2c_ops;
	i2c->adap.retries = 5;
	i2c->adap.class = I2C_CLASS_HWMON;
	i2c->adap.bus_recovery_info = &octeon_i2c_recovery_info;
	i2c->adap.dev.parent = dev;
	i2c->adap.dev.of_node = pdev->dev.of_node;
	snprintf(i2c->adap.name, sizeof(i2c->adap.name),
		 "Cavium ThunderX i2c adapter at %s", dev_name(dev));
	i2c_set_adapdata(&i2c->adap, i2c);

	ret = i2c_add_adapter(&i2c->adap);
	if (ret)
		goto error;

	dev_info(i2c->dev, "Probed. Set system clock to %u\n", i2c->sys_freq);

	ret = thunder_i2c_smbus_setup(i2c, pdev->dev.of_node);
	if (ret)
		dev_info(dev, "SMBUS alert not active on this bus\n");

	return 0;

error:
	thunder_i2c_clock_disable(dev, i2c->clk);
	return ret;
}
