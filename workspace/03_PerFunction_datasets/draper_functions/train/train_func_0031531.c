w1_read_8(struct w1_master *dev)
{
	int i;
	u8 res = 0;

	if (dev->bus_master->read_byte)
		res = dev->bus_master->read_byte(dev->bus_master->data);
	else
		for (i = 0; i < 8; ++i)
			res |= (w1_touch_bit(dev,1) << i);

	return res;
}
