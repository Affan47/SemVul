ds1343_thread(int irq, void *dev_id)
{
	struct ds1343_priv *priv = dev_id;
	unsigned int stat, control;
	int res = 0;

	mutex_lock(&priv->mutex);

	res = regmap_read(priv->map, DS1343_STATUS_REG, &stat);
	if (res)
		goto out;

	if (stat & DS1343_IRQF0) {
		stat &= ~DS1343_IRQF0;
		regmap_write(priv->map, DS1343_STATUS_REG, stat);

		res = regmap_read(priv->map, DS1343_CONTROL_REG, &control);
		if (res)
			goto out;

		control &= ~DS1343_A0IE;
		regmap_write(priv->map, DS1343_CONTROL_REG, control);

		rtc_update_irq(priv->rtc, 1, RTC_AF | RTC_IRQF);
	}

out:
	mutex_unlock(&priv->mutex);
	return IRQ_HANDLED;
}
