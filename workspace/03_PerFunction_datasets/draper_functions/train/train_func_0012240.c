dev_probe(void)
{
	int		retc;
	int		retmsg;
	unsigned char	type;

	if ((retc = read (P_mfd, Holdbuf, 1)) == -1) {
		if (errno == EIO) {
			retc = 0;
		} else {
			sysmessage(MSG_ERR,
					"Can't read from master pty: %s\n",
					strerror(errno));
			return (retc);
		}
	}

	if (Debug > 2) {
		sysmessage (MSG_DEBUG, "PROBE: %d bytes: %d", retc, Holdbuf[0]);
	}
	if (retc != 0) {
		type = Holdbuf[0];
		if (type == TIOCPKT_DATA) {
			retmsg = PROBE_DATA;
		} else if (type & (TIOCPKT_FLUSHREAD|TIOCPKT_FLUSHWRITE)){
			retmsg = PROBE_FLUSH;
		} else {
			retmsg = PROBE_GENERIC;
		}
		Hold = TRUE;
	} else {
		retmsg = PROBE_EOF;
	}
	if (Debug > 1) {
		sysmessage (MSG_DEBUG, "PROBE: msg %d\n", retmsg);
	}
	return (retmsg);
}
