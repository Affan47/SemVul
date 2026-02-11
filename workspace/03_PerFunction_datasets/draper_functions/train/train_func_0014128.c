nct6775_pwm_is_visible(struct kobject *kobj,
				      struct attribute *attr, int index)
{
	struct device *dev = container_of(kobj, struct device, kobj);
	struct nct6775_data *data = dev_get_drvdata(dev);
	int pwm = index / 36;
	int nr = index % 36;

	if (!(data->has_pwm & (1 << pwm)))
		return 0;

	if ((nr >= 14 && nr <= 18) || nr == 21)
		if (!data->REG_WEIGHT_TEMP_SEL[pwm])
			return 0;
	if (nr == 19 && data->REG_PWM[3] == NULL)
		return 0;
	if (nr == 20 && data->REG_PWM[4] == NULL)
		return 0;
	if (nr == 21 && data->REG_PWM[6] == NULL)
		return 0;

	if (nr >= 22 && nr <= 35) {
		int api = (nr - 22) / 2;

		if (api > data->auto_pwm_num)
			return 0;
	}
	return attr->mode;
}
