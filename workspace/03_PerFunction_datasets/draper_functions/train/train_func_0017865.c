mt9v032_set_power(struct v4l2_subdev *subdev, int on)
{
	struct mt9v032 *mt9v032 = to_mt9v032(subdev);
	int ret = 0;

	mutex_lock(&mt9v032->power_lock);


	if (mt9v032->power_count == !on) {
		ret = __mt9v032_set_power(mt9v032, !!on);
		if (ret < 0)
			goto done;
	}


	mt9v032->power_count += on ? 1 : -1;
	WARN_ON(mt9v032->power_count < 0);

done:
	mutex_unlock(&mt9v032->power_lock);
	return ret;
}
