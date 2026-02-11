i2c_send(int dev, uint8_t addr, uint8_t data)
{
	char buf[2];
	buf[0] = addr;
	buf[1] = data;
	if ((write(dev, buf, 2)) != 2) {
		return -1;
	}
	return 0;
}
