sms_msgdata_len(Msg* msg)
{
	int ret = 0;
	Octstr* msgdata = NULL;


	if (!msg || !msg->sms.msgdata)
		return -1;

	if (msg->sms.coding == DC_7BIT) {
		msgdata = octstr_duplicate(msg->sms.msgdata);
		charset_utf8_to_gsm(msgdata);
		ret = octstr_len(msgdata);
		octstr_destroy(msgdata);
	} else
		ret = octstr_len(msg->sms.msgdata);

	return ret;
}
