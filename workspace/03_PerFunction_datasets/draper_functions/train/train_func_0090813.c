play_iframe(struct av7110 *av7110, char __user *buf, unsigned int len, int nonblock)
{
	unsigned i, n;
	int progressive = 0;
	int match = 0;

	dprintk(2, "av7110:%p, \n", av7110);

	if (!(av7110->playing & RP_VIDEO)) {
		if (av7110_av_start_play(av7110, RP_VIDEO) < 0)
			return -EBUSY;
	}


	for (i = 0; i < len; i++) {
		unsigned char c;
		if (get_user(c, buf + i))
			return -EFAULT;
		if (match == 5) {
			progressive = c & 0x08;
			match = 0;
		}
		if (c == 0x00) {
			match = (match == 1 || match == 2) ? 2 : 1;
			continue;
		}
		switch (match++) {
		case 2: if (c == 0x01)
				continue;
			break;
		case 3: if (c == 0xb5)
				continue;
			break;
		case 4: if ((c & 0xf0) == 0x10)
				continue;
			break;
		}
		match = 0;
	}


	n = MIN_IFRAME / len + 1;


	dvb_play_kernel(av7110, iframe_header, sizeof(iframe_header), 0, 1);

	for (i = 0; i < n; i++)
		dvb_play(av7110, buf, len, 0, 1);

	av7110_ipack_flush(&av7110->ipack[1]);

	if (progressive)
		return vidcom(av7110, AV_VIDEO_CMD_FREEZE, 1);
	else
		return 0;
}
