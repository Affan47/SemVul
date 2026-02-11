adv7511_hpd(struct adv7511 *adv7511)
{
	unsigned int irq0;
	int ret;

	ret = regmap_read(adv7511->regmap, ADV7511_REG_INT(0), &irq0);
	if (ret < 0)
		return false;

	if (irq0 & ADV7511_INT0_HDP) {
		regmap_write(adv7511->regmap, ADV7511_REG_INT(0),
			     ADV7511_INT0_HDP);
		return true;
	}

	return false;
}
