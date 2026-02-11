dib9000_fw_boot(struct dib9000_state *state, const u8 * codeA, u32 lenA, const u8 * codeB, u32 lenB)
{

	dib9000_write_word(state, 1225, 0x02);
	dib9000_write_word(state, 1226, 0x05);


	dib9000_write_word(state, 1542, 1);


	dib9000_write_word(state, 1074, 0);
	dib9000_write_word(state, 1075, 0);


	dib9000_write_word(state, 1237, 0);


	if (codeA != NULL)
		dib9000_write_word(state, 1024, 2);
	else
		dib9000_write_word(state, 1024, 15);
	if (codeB != NULL)
		dib9000_write_word(state, 1040, 2);

	if (codeA != NULL)
		dib9000_firmware_download(state, 0, 0x1234, codeA, lenA);
	if (codeB != NULL)
		dib9000_firmware_download(state, 1, 0x1234, codeB, lenB);


	if (codeA != NULL)
		dib9000_write_word(state, 1024, 0);
	if (codeB != NULL)
		dib9000_write_word(state, 1040, 0);

	if (codeA != NULL)
		if (dib9000_mbx_host_init(state, 0) != 0)
			return -EIO;
	if (codeB != NULL)
		if (dib9000_mbx_host_init(state, 1) != 0)
			return -EIO;

	msleep(100);
	state->platform.risc.fw_is_running = 1;

	if (dib9000_risc_check_version(state) != 0)
		return -EINVAL;

	state->platform.risc.memcmd = 0xff;
	return 0;
}
