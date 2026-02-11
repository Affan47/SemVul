bq24257_resume(struct device *dev)
{
	int ret;
	struct bq24257_device *bq = dev_get_drvdata(dev);

	ret = regcache_drop_region(bq->rmap, BQ24257_REG_1, BQ24257_REG_7);
	if (ret < 0)
		return ret;

	ret = bq24257_field_write(bq, F_RESET, 0);
	if (ret < 0)
		return ret;

	ret = bq24257_hw_init(bq);
	if (ret < 0) {
		dev_err(bq->dev, "Cannot init chip after resume.\n");
		return ret;
	}


	power_supply_changed(bq->charger);

	return 0;
}
