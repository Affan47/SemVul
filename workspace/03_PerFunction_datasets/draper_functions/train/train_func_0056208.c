uploadack(aim_session_t *sess, aim_module_t *mod, aim_frame_t *rx,
	aim_modsnac_t *snac, aim_bstream_t *bs)
{
	int ret = 0;
	aim_rxcallback_t userfunc;
	fu16_t something, somethingelse;
	fu8_t onemorething;

	something = aimbs_get16(bs);
	somethingelse = aimbs_get16(bs);
	onemorething = aimbs_get8(bs);

	if ((userfunc = aim_callhandler(sess, rx->conn, snac->family,
				snac->subtype)))
		ret = userfunc(sess, rx);

	return ret;
}
