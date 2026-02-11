ma600_change_speed(struct sir_dev *dev, unsigned speed)
{
	u8	byte;

	pr_debug("%s(), speed=%d (was %d)\n", __func__,
		 speed, dev->speed);


	sirdev_set_dtr_rts(dev, TRUE, FALSE);
	mdelay(1);


	byte = get_control_byte(speed);
	sirdev_raw_write(dev, &byte, sizeof(byte));


	msleep(15);

#if 1


	sirdev_raw_read(dev, &byte, sizeof(byte));
	if (byte != get_control_byte(speed))  {
		net_warn_ratelimited("%s(): bad control byte read-back %02x != %02x\n",
				     __func__, (unsigned)byte,
				     (unsigned)get_control_byte(speed));
		return -1;
	}
	else
		pr_debug("%s() control byte write read OK\n", __func__);
#endif


	sirdev_set_dtr_rts(dev, TRUE, TRUE);


	msleep(10);


	dev->speed = speed;

	return 0;
}
