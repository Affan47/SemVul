handlehdr_odc(aim_session_t *sess, aim_conn_t *conn,
	aim_frame_t *frr, aim_bstream_t *bs)
{
	aim_frame_t fr;
	int ret = 0;
	aim_rxcallback_t userfunc;
	fu32_t payloadlength;
	fu16_t flags, encoding;
	char *snptr = NULL;

	fr.conn = conn;


	aim_bstream_setpos(bs, 20);
	payloadlength = aimbs_get32(bs);

	aim_bstream_setpos(bs, 24);
	encoding = aimbs_get16(bs);

	aim_bstream_setpos(bs, 30);
	flags = aimbs_get16(bs);

	aim_bstream_setpos(bs, 36);

	snptr = aimbs_getstr(bs, 32);

	faimdprintf(sess, 2,
		"faim: OFT frame: handlehdr_odc: %04x / %04x / %s\n",
		payloadlength, flags, snptr);

	if (flags & 0x0008) {
		if ((userfunc = aim_callhandler(sess, conn, AIM_CB_FAM_OFT,
					AIM_CB_OFT_DIRECTIMTYPING)))
			ret = userfunc(sess, &fr, snptr, 2);
	} else if (flags & 0x0004) {
		if ((userfunc = aim_callhandler(sess, conn, AIM_CB_FAM_OFT,
					AIM_CB_OFT_DIRECTIMTYPING)))
			ret = userfunc(sess, &fr, snptr, 1);
	} else {
		if ((userfunc = aim_callhandler(sess, conn, AIM_CB_FAM_OFT,
					AIM_CB_OFT_DIRECTIMTYPING)))
			ret = userfunc(sess, &fr, snptr, 0);
	}

	if (payloadlength) {
		char *msg;
		int recvd = 0;
		int i, isawaymsg;

		isawaymsg = flags & 0x0001;

		if (!(msg = calloc(1, payloadlength + 1))) {
			free(snptr);
			return -ENOMEM;
		}

		while (payloadlength - recvd) {
			if (payloadlength - recvd >= 1024)
				i = aim_recv(conn->fd, &msg[recvd], 1024);
			else
				i = aim_recv(conn->fd, &msg[recvd],
					payloadlength - recvd);
			if (i <= 0) {
				free(msg);
				free(snptr);
				return -1;
			}
			recvd = recvd + i;
			if ((userfunc = aim_callhandler(sess, conn,
						AIM_CB_FAM_SPECIAL,
						AIM_CB_SPECIAL_IMAGETRANSFER)))
				ret = userfunc(sess, &fr, snptr,
					(double)recvd / payloadlength);
		}

		if ((userfunc = aim_callhandler(sess, conn, AIM_CB_FAM_OFT,
					AIM_CB_OFT_DIRECTIMINCOMING)))
			ret = userfunc(sess, &fr, snptr, msg, payloadlength,
				encoding, isawaymsg);

		free(msg);
	}

	free(snptr);

	return ret;
}
