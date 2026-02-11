aim_locate_setprofile(aim_session_t *sess,
	const char *profile_encoding, const char *profile,
	const int profile_len, const char *awaymsg_encoding,
	const char *awaymsg, const int awaymsg_len, fu32_t caps)
{
	aim_conn_t *conn;
	aim_frame_t *fr;
	aim_snacid_t snacid;
	aim_tlvlist_t *tl = NULL;
	char *encoding;
	static const char defencoding[] = { "text/aolrtf; charset=\"%s\"" };

	if (!sess || !(conn = aim_conn_findbygroup(sess, AIM_CB_FAM_LOC)))
		return -EINVAL;

	if ((profile && profile_encoding == NULL) || (awaymsg && awaymsg_len
			&& awaymsg_encoding == NULL)) {
		return -EINVAL;
	}


	if (profile) {

		encoding =
			malloc(strlen(defencoding) + strlen(profile_encoding));
		if (encoding == NULL) {
			return -ENOMEM;
		}
		snprintf(encoding,
			strlen(defencoding) + strlen(profile_encoding),
			defencoding, profile_encoding);
		aim_addtlvtochain_raw(&tl, 0x0001, strlen(encoding), encoding);
		aim_addtlvtochain_raw(&tl, 0x0002, profile_len, profile);
		free(encoding);
	}


	if (awaymsg) {
		if (awaymsg_len) {
			encoding =
				malloc(strlen(defencoding) +
				strlen(awaymsg_encoding));
			if (encoding == NULL) {
				return -ENOMEM;
			}
			snprintf(encoding,
				strlen(defencoding) + strlen(awaymsg_encoding),
				defencoding, awaymsg_encoding);
			aim_addtlvtochain_raw(&tl, 0x0003, strlen(encoding),
				encoding);
			aim_addtlvtochain_raw(&tl, 0x0004, awaymsg_len,
				awaymsg);
			free(encoding);
		} else
			aim_addtlvtochain_noval(&tl, 0x0004);
	}

	aim_addtlvtochain_caps(&tl, 0x0005, caps);

	if (!(fr = aim_tx_new(sess, conn, AIM_FRAMETYPE_FLAP, 0x02,
				10 + aim_sizetlvchain(&tl))))
		return -ENOMEM;

	snacid = aim_cachesnac(sess, 0x0002, 0x0004, 0x0000, NULL, 0);
	aim_putsnac(&fr->data, 0x0002, 0x004, 0x0000, snacid);

	aim_writetlvchain(&fr->data, &tl);
	aim_freetlvchain(&tl);

	aim_tx_enqueue(sess, fr);

	return 0;
}
