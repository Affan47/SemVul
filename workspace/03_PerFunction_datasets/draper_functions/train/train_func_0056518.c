aim_sendpauseack(aim_session_t *sess, aim_conn_t *conn)
{
	aim_frame_t *fr;
	aim_snacid_t snacid;
	aim_conn_inside_t *ins = (aim_conn_inside_t *)conn->inside;
	struct snacgroup *sg;

	if (!(fr = aim_tx_new(sess, conn, AIM_FRAMETYPE_FLAP, 0x02, 1024)))
		return -ENOMEM;

	snacid = aim_cachesnac(sess, 0x0001, 0x000c, 0x0000, NULL, 0);
	aim_putsnac(&fr->data, 0x0001, 0x000c, 0x0000, snacid);


	for (sg = ins->groups; sg; sg = sg->next)
		aimbs_put16(&fr->data, sg->group);

	aim_tx_enqueue(sess, fr);

	return 0;
}
