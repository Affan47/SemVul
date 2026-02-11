skytraq_wait_reply(int fd, uint8_t reply, uint8_t *buf, uint8_t reply_len) {

	for(;;) {
		uint8_t	a, b;
		uint8_t	cksum_computed, cksum_read;
		int	len;
		switch (skytraq_expect(fd, 0xa0, 10000)) {
		case -1:
			return -1;
		case 0:
			continue;
		case 1:
			break;
		}
		switch (skytraq_expect(fd, 0xa1, 1000)) {
		case -1:
			return -1;
		case 0:
			continue;
		}
		a = skytraq_waitchar(fd, 1000);
		b = skytraq_waitchar(fd, 1000);
		switch (skytraq_expect(fd, reply, 1000)) {
		case -1:
			return -1;
		case 0:
			continue;
		}
		len = (a << 16) | b;
		if (len != reply_len)
			continue;
		*buf++ = reply;
		len--;
		cksum_computed = reply;
		while (len--) {
			a = skytraq_waitchar(fd, 1000);
			if (a < 0)
				return a;
			cksum_computed ^= a;
			*buf++ = a;
		}
		switch (skytraq_expect(fd, cksum_computed, 1000)) {
		case -1:
			return -1;
		case 0:
			continue;
		}
		switch (skytraq_expect(fd, 0x0d, 1000)) {
		case -1:
			return -1;
		case 0:
			continue;
		}
		switch (skytraq_expect(fd, 0x0a, 1000)) {
		case -1:
			return -1;
		case 0:
			continue;
		}
		break;
	}
	return 0;
}
