aedsp16_write(int port, int cmd)
{
	unsigned char   ret;
	int             loop = HARDRETRY;

	DBG(("    Write DSP Byte (0x%x) [0x%x]: ", port, cmd));

	do {
		ret = inb(port + DSP_STATUS);


		if (!(ret & 0x80)) {
			outb(cmd, port + DSP_COMMAND);
			DBG(("success.\n"));
			return 0;
		}
	} while (loop--);

	DBG(("timeout.\n"));
	printk("[AEDSP16] DSP Command (0x%x) timeout.\n", cmd);

	return -1;
}
