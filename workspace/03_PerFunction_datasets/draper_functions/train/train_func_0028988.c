aim_im_setparams(aim_session_t *sess,
	struct aim_icbmparameters *params)
{
	aim_conn_t *conn;
	aim_frame_t *fr;
	aim_snacid_t snacid;

	if (!sess || !(conn = aim_conn_findbygroup(sess, 0x0004)))
		return -EINVAL;

	if (!params)
		return -EINVAL;

	if (!(fr = aim_tx_new(sess, conn, AIM_FRAMETYPE_FLAP, 0x02, 10 + 16)))
		return -ENOMEM;

	snacid = aim_cachesnac(sess, 0x0004, 0x0002, 0x0000, NULL, 0);
	aim_putsnac(&fr->data, 0x0004, 0x0002, 0x0000, snacid);


	aimbs_put16(&fr->data, 0x0000);


	aimbs_put32(&fr->data, params->flags);
	aimbs_put16(&fr->data, params->maxmsglen);
	aimbs_put16(&fr->data, params->maxsenderwarn);
	aimbs_put16(&fr->data, params->maxrecverwarn);
	aimbs_put32(&fr->data, params->minmsginterval);

	aim_tx_enqueue(sess, fr);

	return 0;
}
