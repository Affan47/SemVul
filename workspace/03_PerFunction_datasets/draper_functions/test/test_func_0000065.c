incomingim_ch1(aim_session_t *sess, aim_module_t *mod,
	aim_frame_t *rx, aim_modsnac_t *snac, fu16_t channel,
	aim_userinfo_t *userinfo, aim_bstream_t *bs, fu8_t *cookie)
{
	fu16_t type, length;
	aim_rxcallback_t userfunc;
	int ret = 0;
	struct aim_incomingim_ch1_args args;
	int endpos;

	memset(&args, 0, sizeof(args));

	aim_mpmsg_init(sess, &args.mpmsg);


	while (aim_bstream_empty(bs)) {

		type = aimbs_get16(bs);
		length = aimbs_get16(bs);

		endpos = aim_bstream_curpos(bs) + length;

		if (type == 0x0002) {


			aimbs_get8(bs);
			aimbs_get8(bs);

			args.featureslen = aimbs_get16(bs);

			args.features = bs->data + bs->offset;
			aim_bstream_advance(bs, args.featureslen);
			args.icbmflags |= AIM_IMFLAGS_CUSTOMFEATURES;


			incomingim_ch1_parsemsgs(sess,
				bs->data + bs->offset  ,
				length - 2 - 2 - args.featureslen, &args);

		} else if (type == 0x0003) {

			args.icbmflags |= AIM_IMFLAGS_ACK;

		} else if (type == 0x0004) {

			args.icbmflags |= AIM_IMFLAGS_AWAY;

		} else if (type == 0x0006) {


			args.icbmflags |= AIM_IMFLAGS_OFFLINE;

		} else if (type == 0x0008) {

			args.iconlen = aimbs_get32(bs);
			aimbs_get16(bs);
			args.iconsum = aimbs_get16(bs);
			args.iconstamp = aimbs_get32(bs);


			if (args.iconlen)
				args.icbmflags |= AIM_IMFLAGS_HASICON;

		} else if (type == 0x0009) {

			args.icbmflags |= AIM_IMFLAGS_BUDDYREQ;

		} else if (type == 0x000b) {

			args.icbmflags |= AIM_IMFLAGS_TYPINGNOT;

		} else if (type == 0x0017) {

			args.extdatalen = length;
			args.extdata = aimbs_getraw(bs, args.extdatalen);

		} else {
			faimdprintf(sess, 0,
				"incomingim_ch1: unknown TLV 0x%04x (len %d)\n",
				type, length);
		}


		aim_bstream_setpos(bs, endpos);
	}

	if ((userfunc = aim_callhandler(sess, rx->conn, snac->family,
				snac->subtype)))
		ret = userfunc(sess, rx, channel, userinfo, &args);

	aim_mpmsg_free(sess, &args.mpmsg);
	free(args.extdata);

	return ret;
}
