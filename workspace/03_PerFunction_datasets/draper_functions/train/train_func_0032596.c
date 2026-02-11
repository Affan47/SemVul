l3dss1_alert_req(struct l3_process *pc, u_char pr,
		 void *arg)
{
	newl3state(pc, 7);
	if (!pc->prot.dss1.uus1_data[0])
		l3dss1_message(pc, MT_ALERTING);
	else
		l3dss1_msg_with_uus(pc, MT_ALERTING);
}
