send_option (int type, int opt)
{
	int ret;
	int size;
	unsigned char *obp;

	obp = &Comobuf[0];

	*obp++ = IAC;
	*obp++ = type;
	*obp++ = opt;

	size = 3;
	obp = &Comobuf[0];

	if (Debug > 2) {
	sysmessage (MSG_DEBUG, "Sock_write, 3 bytes: %02X %02X %02X\n",
			Comobuf[0], Comobuf[1], Comobuf[2]);
	}

	while (size) {
		if ((ret = sock_write (obp, size)) == -1) {
			SET_EVENT(EV_RN, EV_RNHANG, 0, 0);
			break;
		} else if (ret != size) {
			sysmessage (MSG_NOTICE,
			"Partial write in send_option: %d/%d\n",
					ret, size);
			sysdelay(ROOM_DELAY);
		}
		size -= ret;
		obp += ret;
	}
}
