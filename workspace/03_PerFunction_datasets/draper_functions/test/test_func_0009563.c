lm3639_flash_brightness_set(struct led_classdev *cdev,
					enum led_brightness brightness)
{
	int ret;
	unsigned int reg_val;
	struct lm3639_chip_data *pchip;

	pchip = container_of(cdev, struct lm3639_chip_data, cdev_flash);

	ret = regmap_read(pchip->regmap, REG_FLAG, &reg_val);
	if (ret < 0)
		goto out;
	if (reg_val != 0)
		dev_info(pchip->dev, "last flag is 0x%x\n", reg_val);


	ret = regmap_update_bits(pchip->regmap, REG_ENABLE, 0x06, 0x00);
	if (ret < 0)
		goto out;


	if (!brightness)
		return;

	ret = regmap_update_bits(pchip->regmap,
				 REG_FL_CONF_1, 0x0F, brightness - 1);
	if (ret < 0)
		goto out;
	ret = regmap_update_bits(pchip->regmap, REG_ENABLE, 0x06, 0x06);
	if (ret < 0)
		goto out;

	return;
out:
	dev_err(pchip->dev, "i2c failed to access register\n");
}
