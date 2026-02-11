send_autopilot_msgID(int msgid)
{
	if (msgid < 0 || msgid > NP_NUM_MESSAGES)
		return;

	send_autopilot_msg(NavMsgs[msgid].message, NavMsgs[msgid].filename);
}
