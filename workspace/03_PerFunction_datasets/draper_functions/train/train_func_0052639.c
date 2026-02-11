parsedel(aim_session_t *sess, aim_module_t *mod, aim_frame_t *rx,
	aim_modsnac_t *snac, aim_bstream_t *bs)
{
	int ret = 0;
	aim_rxcallback_t userfunc;
	fu16_t gid, bid;
	struct aim_ssi_item *del;

	while (aim_bstream_empty(bs)) {
		aim_bstream_advance(bs, aimbs_get16(bs));
		gid = aimbs_get16(bs);
		bid = aimbs_get16(bs);
		aimbs_get16(bs);
		aim_bstream_advance(bs, aimbs_get16(bs));

		if ((del = aim_ssi_itemlist_find(sess->ssi.local, gid, bid)))
			aim_ssi_itemlist_del(&sess->ssi.local, del);
		if ((del = aim_ssi_itemlist_find(sess->ssi.official, gid, bid)))
			aim_ssi_itemlist_del(&sess->ssi.official, del);

		if ((userfunc = aim_callhandler(sess, rx->conn, snac->family,
					snac->subtype)))
			ret = userfunc(sess, rx);
	}

	return ret;
}
