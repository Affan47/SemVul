imm_init(imm_struct *dev)
{
	if (imm_connect(dev, 0) != 1)
		return -EIO;
	imm_reset_pulse(dev->base);
	mdelay(1);
	imm_disconnect(dev);
	mdelay(1);
	return device_check(dev);
}
