aim_locate_setdirinfo(aim_session_t *sess, const char *first,
	const char *middle, const char *last, const char *maiden,
	const char *nickname, const char *street, const char *city,
	const char *state, const char *zip, int country, fu16_t privacy)
{
	aim_conn_t *conn;
	aim_frame_t *fr;
	aim_snacid_t snacid;
	aim_tlvlist_t *tl = NULL;

	if (!sess || !(conn = aim_conn_findbygroup(sess, AIM_CB_FAM_LOC)))
		return -EINVAL;

	aim_addtlvtochain16(&tl, 0x000a, privacy);

	if (first)
		aim_addtlvtochain_raw(&tl, 0x0001, strlen(first), first);
	if (last)
		aim_addtlvtochain_raw(&tl, 0x0002, strlen(last), last);
	if (middle)
		aim_addtlvtochain_raw(&tl, 0x0003, strlen(middle), middle);
	if (maiden)
		aim_addtlvtochain_raw(&tl, 0x0004, strlen(maiden), maiden);

	if (state)
		aim_addtlvtochain_raw(&tl, 0x0007, strlen(state), state);
	if (city)
		aim_addtlvtochain_raw(&tl, 0x0008, strlen(city), city);

	if (nickname)
		aim_addtlvtochain_raw(&tl, 0x000c, strlen(nickname), nickname);
	if (zip)
		aim_addtlvtochain_raw(&tl, 0x000d, strlen(zip), zip);

	if (street)
		aim_addtlvtochain_raw(&tl, 0x0021, strlen(street), street);

	if (!(fr = aim_tx_new(sess, conn, AIM_FRAMETYPE_FLAP, 0x02,
				10 + aim_sizetlvchain(&tl))))
		return -ENOMEM;

	snacid = aim_cachesnac(sess, 0x0002, 0x0009, 0x0000, NULL, 0);

	aim_putsnac(&fr->data, 0x0002, 0x0009, 0x0000, snacid);
	aim_writetlvchain(&fr->data, &tl);
	aim_freetlvchain(&tl);

	aim_tx_enqueue(sess, fr);

	return 0;
}
