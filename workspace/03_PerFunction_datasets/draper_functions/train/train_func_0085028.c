rpc_setup(struct evhttp **phttp, short *pport, struct evrpc_base **pbase)
{
	short port;
	struct evhttp *http = NULL;
	struct evrpc_base *base = NULL;

	http = http_setup(&port);
	base = evrpc_init(http);

	EVRPC_REGISTER(base, Message, msg, kill, MessageCb, NULL);
	EVRPC_REGISTER(base, NeverReply, msg, kill, NeverReplyCb, NULL);

	*phttp = http;
	*pport = port;
	*pbase = base;

	need_input_hook = 0;
	need_output_hook = 0;
}
