receiveauthrequest(aim_session_t *sess, aim_module_t *mod,
	aim_frame_t *rx, aim_modsnac_t *snac, aim_bstream_t *bs)
{
	int ret = 0;
	aim_rxcallback_t userfunc;
	fu16_t tmp;
	char *sn, *msg;


	if ((tmp = aimbs_get8(bs)))
		sn = aimbs_getstr(bs, tmp);
	else
		sn = NULL;


	if ((tmp = aimbs_get16(bs)))
		msg = aimbs_getstr(bs, tmp);
	else
		msg = NULL;


	tmp = aimbs_get16(bs);

	if ((userfunc = aim_callhandler(sess, rx->conn, snac->family,
				snac->subtype)))
		ret = userfunc(sess, rx, sn, msg);

	free(sn);
	free(msg);

	return ret;
}
