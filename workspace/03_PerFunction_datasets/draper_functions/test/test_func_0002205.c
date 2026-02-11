aim_mpmsg_addunicode(aim_session_t *sess, aim_mpmsg_t *mpm,
	const fu16_t *unicode, fu16_t unicodelen)
{
	fu8_t *buf;
	aim_bstream_t bs;
	int i;

	if (!(buf = malloc(unicodelen * 2)))
		return -1;

	aim_bstream_init(&bs, buf, unicodelen * 2);


	for (i = 0; i < unicodelen; i++)
		aimbs_put16(&bs, unicode[i]);

	if (mpmsg_addsection(sess, mpm, 0x0002, 0x0000, buf,
			aim_bstream_curpos(&bs)) == -1) {
		free(buf);
		return -1;
	}

	return 0;
}
