sch311x_gpio_probe(struct platform_device *pdev)
{
	struct sch311x_pdev_data *pdata = pdev->dev.platform_data;
	struct sch311x_gpio_priv *priv;
	struct sch311x_gpio_block *block;
	int err, i;


	if (!request_region(pdata->runtime_reg + GP1, 6, DRV_NAME)) {
		dev_err(&pdev->dev, "Failed to request region 0x%04x-0x%04x.\n",
			pdata->runtime_reg + GP1, pdata->runtime_reg + GP1 + 5);
		return -EBUSY;
	}

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	platform_set_drvdata(pdev, priv);

	for (i = 0; i < ARRAY_SIZE(priv->blocks); i++) {
		block = &priv->blocks[i];

		spin_lock_init(&block->lock);

		block->chip.label = DRV_NAME;
		block->chip.owner = THIS_MODULE;
		block->chip.request = sch311x_gpio_request;
		block->chip.free = sch311x_gpio_free;
		block->chip.direction_input = sch311x_gpio_direction_in;
		block->chip.direction_output = sch311x_gpio_direction_out;
		block->chip.get = sch311x_gpio_get;
		block->chip.set = sch311x_gpio_set;
		block->chip.ngpio = 8;
		block->chip.dev = &pdev->dev;
		block->chip.base = sch311x_gpio_blocks[i].base;
		block->config_regs = sch311x_gpio_blocks[i].config_regs;
		block->data_reg = sch311x_gpio_blocks[i].data_reg;
		block->runtime_reg = pdata->runtime_reg;

		err = gpiochip_add(&block->chip);
		if (err < 0) {
			dev_err(&pdev->dev,
				"Could not register gpiochip, %d\n", err);
			goto exit_err;
		}
		dev_info(&pdev->dev,
			 "SMSC SCH311x GPIO block %d registered.\n", i);
	}

	return 0;

exit_err:
	release_region(pdata->runtime_reg + GP1, 6);

	for (--i; i >= 0; i--)
		gpiochip_remove(&priv->blocks[i].chip);
	return err;
}
