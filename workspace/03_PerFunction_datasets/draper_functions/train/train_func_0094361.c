lp855x_remove(struct i2c_client *cl)
{
	struct lp855x *lp = i2c_get_clientdata(cl);

	lp->bl->props.brightness = 0;
	backlight_update_status(lp->bl);
	if (lp->supply)
		regulator_disable(lp->supply);
	sysfs_remove_group(&lp->dev->kobj, &lp855x_attr_group);

	return 0;
}
