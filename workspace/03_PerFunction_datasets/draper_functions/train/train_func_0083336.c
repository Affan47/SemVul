WriteMiscWord(uint16_t addr, uint32_t len,
		uint8_t kind, uint16_t *wr)
{
	uint8_t wmw[64] = {0};
	wmw[0] = COMMAND_WRITE_MISC | 0x05;
	wmw[1] = kind;

	while (len--) {
		wmw[2] = addr >> 8;
		wmw[3] = addr & 0xFF;
		++addr;
		wmw[4] = *wr >> 8;
		wmw[5] = *wr & 0xFF;
		++wr;

		int err;
		if ((err = HID_WriteReport(wmw)))
			return err;

		uint8_t rsp[68];
		if ((err = HID_ReadReport(rsp)))
			return err;
		if ((rsp[0] & COMMAND_MASK) != RESPONSE_DONE ||
			rsp[1] != COMMAND_WRITE_MISC) {
			return 1;
		}
	}
	return 0;
}
