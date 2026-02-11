read_smc(u8 cmd, const char *key, u8 *buffer, u8 len)
{
	u8 status, data = 0;
	int i;

	if (send_command(cmd) || send_argument(key)) {
		pr_warn("%.4s: read arg fail\n", key);
		return -EIO;
	}


	if (send_byte(len, APPLESMC_DATA_PORT)) {
		pr_warn("%.4s: read len fail\n", key);
		return -EIO;
	}

	for (i = 0; i < len; i++) {
		if (wait_read()) {
			pr_warn("%.4s: read data[%d] fail\n", key, i);
			return -EIO;
		}
		buffer[i] = inb(APPLESMC_DATA_PORT);
	}


	for (i = 0; i < 16; i++) {
		udelay(APPLESMC_MIN_WAIT);
		status = inb(APPLESMC_CMD_PORT);
		if (!(status & 0x01))
			break;
		data = inb(APPLESMC_DATA_PORT);
	}
	if (i)
		pr_warn("flushed %d bytes, last value is: %d\n", i, data);

	return 0;
}
