go7007_read_addr(struct go7007 *go, u16 addr, u16 *data)
{
	int count = 100;
	u16 value;

	if (go7007_write_interrupt(go, 0x0010, addr) < 0)
		return -EIO;
	while (count-- > 0) {
		if (go7007_read_interrupt(go, &value, data) == 0 &&
				value == 0xa000)
			return 0;
	}
	return -EIO;
}
