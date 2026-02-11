write_byte(struct fet_device *dev, address_t addr, uint8_t value)
{
	uint8_t buf[2];
	address_t base = addr & ~1;

	if (xfer(dev, C_READMEMORY, NULL, 0, 2, base, 2) < 0) {
		printc_err("fet: failed to read byte from 0x%04x\n", addr);
		return -1;
	}

	buf[0] = dev->fet_reply.data[0];
	buf[1] = dev->fet_reply.data[1];
	buf[addr & 1] = value;

	if (xfer(dev, C_WRITEMEMORY, buf, 2, 1, base) < 0) {
		printc_err("fet: failed to write byte from 0x%04x\n", addr);
		return -1;
	}

	return 0;
}
