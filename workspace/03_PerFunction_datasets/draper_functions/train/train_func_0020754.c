bochs_dispi_read(struct bochs_device *bochs, u16 reg)
{
	u16 ret = 0;

	if (bochs->mmio) {
		int offset = 0x500 + (reg << 1);
		ret = readw(bochs->mmio + offset);
	} else {
		outw(reg, VBE_DISPI_IOPORT_INDEX);
		ret = inw(VBE_DISPI_IOPORT_DATA);
	}
	return ret;
}
