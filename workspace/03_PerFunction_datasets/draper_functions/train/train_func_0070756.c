aim_ssi_addmoddel(aim_session_t *sess)
{
	aim_conn_t *conn;
	aim_frame_t *fr;
	aim_snacid_t snacid;
	int snaclen;
	struct aim_ssi_tmp *cur;

	if (!sess || !(conn = aim_conn_findbygroup(sess, AIM_CB_FAM_SSI))
		|| !sess->ssi.pending || !sess->ssi.pending->item)
		return -EINVAL;


	snaclen = 10;
	for (cur = sess->ssi.pending; cur; cur = cur->next) {
		snaclen += 10;
		if (cur->item->name)
			snaclen += strlen(cur->item->name);
		if (cur->item->data)
			snaclen += aim_sizetlvchain(&cur->item->data);
	}

	if (!(fr = aim_tx_new(sess, conn, AIM_FRAMETYPE_FLAP, 0x02, snaclen)))
		return -ENOMEM;

	snacid = aim_cachesnac(sess, AIM_CB_FAM_SSI, sess->ssi.pending->action,
		0x0000, NULL, 0);
	aim_putsnac(&fr->data, AIM_CB_FAM_SSI, sess->ssi.pending->action,
		0x0000, snacid);

	for (cur = sess->ssi.pending; cur; cur = cur->next) {
		aimbs_put16(&fr->data,
			cur->item->name ? strlen(cur->item->name) : 0);
		if (cur->item->name)
			aimbs_putraw(&fr->data, cur->item->name,
				strlen(cur->item->name));
		aimbs_put16(&fr->data, cur->item->gid);
		aimbs_put16(&fr->data, cur->item->bid);
		aimbs_put16(&fr->data, cur->item->type);
		aimbs_put16(&fr->data,
			cur->item->data ? aim_sizetlvchain(&cur->item->
				data) : 0);
		if (cur->item->data)
			aim_writetlvchain(&fr->data, &cur->item->data);
	}

	aim_tx_enqueue(sess, fr);

	return 0;
}
