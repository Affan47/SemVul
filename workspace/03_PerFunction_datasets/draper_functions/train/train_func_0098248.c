negchan_middle(aim_session_t *sess, aim_frame_t *fr)
{
	aim_tlvlist_t *tlvlist;
	char *msg = NULL;
	fu16_t code = 0;
	aim_rxcallback_t userfunc;
	int ret = 1;

	if (aim_bstream_empty(&fr->data) == 0) {

		return 1;
	}


	if (fr->conn->type == AIM_CONN_TYPE_AUTH)
		return consumenonsnac(sess, fr, 0x0017, 0x0003);

	tlvlist = aim_readtlvchain(&fr->data);

	if (aim_gettlv(tlvlist, 0x0009, 1))
		code = aim_gettlv16(tlvlist, 0x0009, 1);

	if (aim_gettlv(tlvlist, 0x000b, 1))
		msg = aim_gettlv_str(tlvlist, 0x000b, 1);

	if ((userfunc = aim_callhandler(sess, fr->conn, AIM_CB_FAM_SPECIAL,
				AIM_CB_SPECIAL_CONNERR)))
		ret = userfunc(sess, fr, code, msg);

	aim_freetlvchain(&tlvlist);

	free(msg);

	return ret;
}
