sirdev_set_dongle(struct sir_dev *dev, IRDA_DONGLE type)
{
	int err;

	pr_debug("%s : requesting dongle %d.\n", __func__, type);

	err = sirdev_schedule_dongle_open(dev, type);
	if (unlikely(err))
		return err;
	down(&dev->fsm.sem);
	err = dev->fsm.result;
	up(&dev->fsm.sem);
	return err;
}
