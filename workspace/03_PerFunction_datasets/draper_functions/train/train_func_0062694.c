logmsg_free(struct logmsg *msg)
{
	if (msg->callid) {
		ast_callid_unref(msg->callid);
	}
	ast_free(msg);
}
