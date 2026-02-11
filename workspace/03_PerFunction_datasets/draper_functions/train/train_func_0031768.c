pm860x_backlight_probe(struct platform_device *pdev)
{
	struct pm860x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	struct pm860x_backlight_pdata *pdata = dev_get_platdata(&pdev->dev);
	struct pm860x_backlight_data *data;
	struct backlight_device *bl;
	struct resource *res;
	struct backlight_properties props;
	char name[MFD_NAME_SIZE];
	int ret = 0;

	data = devm_kzalloc(&pdev->dev, sizeof(struct pm860x_backlight_data),
			    GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;
	res = platform_get_resource_byname(pdev, IORESOURCE_REG, "duty cycle");
	if (!res) {
		dev_err(&pdev->dev, "No REG resource for duty cycle\n");
		return -ENXIO;
	}
	data->reg_duty_cycle = res->start;
	res = platform_get_resource_byname(pdev, IORESOURCE_REG, "always on");
	if (!res) {
		dev_err(&pdev->dev, "No REG resource for always on\n");
		return -ENXIO;
	}
	data->reg_always_on = res->start;
	res = platform_get_resource_byname(pdev, IORESOURCE_REG, "current");
	if (!res) {
		dev_err(&pdev->dev, "No REG resource for current\n");
		return -ENXIO;
	}
	data->reg_current = res->start;

	memset(name, 0, MFD_NAME_SIZE);
	sprintf(name, "backlight-%d", pdev->id);
	data->port = pdev->id;
	data->chip = chip;
	data->i2c = (chip->id == CHIP_PM8606) ? chip->client : chip->companion;
	data->current_brightness = MAX_BRIGHTNESS;
	if (pm860x_backlight_dt_init(pdev, data, name)) {
		if (pdata) {
			data->pwm = pdata->pwm;
			data->iset = pdata->iset;
		}
	}

	memset(&props, 0, sizeof(struct backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = MAX_BRIGHTNESS;
	bl = devm_backlight_device_register(&pdev->dev, name, &pdev->dev, data,
					&pm860x_backlight_ops, &props);
	if (IS_ERR(bl)) {
		dev_err(&pdev->dev, "failed to register backlight\n");
		return PTR_ERR(bl);
	}
	bl->props.brightness = MAX_BRIGHTNESS;

	platform_set_drvdata(pdev, bl);


	ret = pm860x_backlight_get_brightness(bl);
	if (ret < 0)
		return ret;

	backlight_update_status(bl);
	return 0;
}
