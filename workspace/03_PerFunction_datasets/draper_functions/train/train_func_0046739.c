mouse_wait_ack(void)
{
	uint32_t timeout;
	uint8_t val;

	for (timeout = 0; ; timeout++) {
		if (timeout == 0x120000) {
			return 4;
		}

		val = inb_p(0x64);

		if (((val >> 5) & 1) == 0) {
			continue;
		}

		val = inb(0x60);
		if (val == REPLY_ACK) {
			return 0;

		} else if (val == REPLY_RESEND) {
			return 3;

		} else {


			return 3;
		}
	}
}
