ao_self_block_write(struct cc_usb *cc, uint32_t address, uint8_t block[256])
{
	int			byte;
	cc_usb_sync(cc);
	cc_usb_printf(cc, "W %x\n", address);
	TRACE ("write %08x\n", address);
	for (byte = 0; byte < 0x100; byte++) {
		TRACE (" %02x", block[byte]);
		if ((byte & 0xf) == 0xf)
			TRACE ("\n");
	}
	for (byte = 0; byte < 0x100; byte++) {
		cc_usb_printf(cc, "%c", block[byte]);
	}
}
