rtl_csi_read(void *ioaddr, int addr)
{
	u32 value = ~0x00;
	unsigned int i;

	DBGP ( "rtl_csi_read\n" );

	RTL_W32(CSIAR, (addr & CSIAR_ADDR_MASK) |
		CSIAR_BYTE_ENABLE << CSIAR_BYTE_ENABLE_SHIFT);

	for (i = 0; i < 100; i++) {
		if (RTL_R32(CSIAR) & CSIAR_FLAG) {
			value = RTL_R32(CSIDR);
			break;
		}
		udelay(10);
	}

	return value;
}
