local_request(const char *type, struct ast_format_cap *cap, const struct ast_channel *requestor, const char *data, int *cause)
{
	struct local_pvt *p;
	struct ast_channel *chan;
	struct ast_callid *callid = ast_read_threadstorage_callid();


	p = local_alloc(data, cap);
	if (!p) {
		chan = NULL;
		goto local_request_end;
	}
	chan = local_new(p, AST_STATE_DOWN, requestor ? ast_channel_linkedid(requestor) : NULL, callid);
	if (!chan) {
		ao2_unlink(locals, p);
	} else if (ast_channel_cc_params_init(chan, requestor ? ast_channel_get_cc_config_params((struct ast_channel *)requestor) : NULL)) {
		ao2_unlink(locals, p);
		p->owner = ast_channel_release(p->owner);
		p->chan = ast_channel_release(p->chan);
		chan = NULL;
	}
	ao2_ref(p, -1);

local_request_end:

	if (callid) {
		ast_callid_unref(callid);
	}

	return chan;
}
