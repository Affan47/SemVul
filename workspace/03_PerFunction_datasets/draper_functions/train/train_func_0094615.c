Reset(uint8_t kind)
{
	uint8_t reset_cmd[64] = { COMMAND_RESET, kind };
	int err;

	err = HID_WriteReport(reset_cmd);


	if (err == -ENODEV) {
		debug("Ignoring error from reset command");
		err = 0;
	}
	return err;
}
