touchscreen_set_params(struct input_dev *dev,
				   unsigned long axis,
				   int max, int fuzz)
{
	struct input_absinfo *absinfo;

	if (!test_bit(axis, dev->absbit)) {
		dev_warn(&dev->dev,
			 "DT specifies parameters but the axis %lu is not set up\n",
			 axis);
		return;
	}

	absinfo = &dev->absinfo[axis];
	absinfo->maximum = max;
	absinfo->fuzz = fuzz;
}
