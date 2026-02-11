bq2415x_set_mode(struct bq2415x_device *bq, enum bq2415x_mode mode)
{
	int ret = 0;
	int charger = 0;
	int boost = 0;

	if (mode == BQ2415X_MODE_BOOST)
		boost = 1;
	else if (mode != BQ2415X_MODE_OFF)
		charger = 1;

	if (!charger)
		ret = bq2415x_exec_command(bq, BQ2415X_CHARGER_DISABLE);

	if (!boost)
		ret = bq2415x_exec_command(bq, BQ2415X_BOOST_MODE_DISABLE);

	if (ret < 0)
		return ret;

	switch (mode) {
	case BQ2415X_MODE_OFF:
		dev_dbg(bq->dev, "changing mode to: Offline\n");
		ret = bq2415x_set_current_limit(bq, 100);
		break;
	case BQ2415X_MODE_NONE:
		dev_dbg(bq->dev, "changing mode to: N/A\n");
		ret = bq2415x_set_current_limit(bq, 100);
		break;
	case BQ2415X_MODE_HOST_CHARGER:
		dev_dbg(bq->dev, "changing mode to: Host/HUB charger\n");
		ret = bq2415x_set_current_limit(bq, 500);
		break;
	case BQ2415X_MODE_DEDICATED_CHARGER:
		dev_dbg(bq->dev, "changing mode to: Dedicated charger\n");
		ret = bq2415x_set_current_limit(bq, 1800);
		break;
	case BQ2415X_MODE_BOOST:
		dev_dbg(bq->dev, "changing mode to: Boost\n");
		ret = bq2415x_set_current_limit(bq, 100);
		break;
	}

	if (ret < 0)
		return ret;

	if (charger)
		ret = bq2415x_exec_command(bq, BQ2415X_CHARGER_ENABLE);
	else if (boost)
		ret = bq2415x_exec_command(bq, BQ2415X_BOOST_MODE_ENABLE);

	if (ret < 0)
		return ret;

	bq2415x_set_default_value(bq, weak_battery_voltage);
	bq2415x_set_default_value(bq, battery_regulation_voltage);

	bq->mode = mode;
	sysfs_notify(&bq->charger->dev.kobj, NULL, "mode");

	return 0;

}
