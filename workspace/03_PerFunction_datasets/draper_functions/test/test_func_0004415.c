rpc_basic_queued_client(void)
{
	short port;
	struct evhttp *http = NULL;
	struct evrpc_base *base = NULL;
	struct evrpc_pool *pool = NULL;
	struct msg *msg;
	struct kill *kill_one, *kill_two;

	fprintf(stdout, "Testing RPC (Queued) Client: ");

	rpc_setup(&http, &port, &base);

	pool = rpc_pool_with_connection(port);


	msg = msg_new();
	EVTAG_ASSIGN(msg, from_name, "niels");
	EVTAG_ASSIGN(msg, to_name, "tester");

	kill_one = kill_new();
	kill_two = kill_new();

	EVRPC_MAKE_REQUEST(Message, pool, msg, kill_one,  GotKillCbTwo, NULL);
	EVRPC_MAKE_REQUEST(Message, pool, msg, kill_two,  GotKillCb, NULL);

	test_ok = 0;

	event_dispatch();

	rpc_teardown(base);

	if (test_ok != 2) {
		fprintf(stdout, "FAILED (1)\n");
		exit(1);
	}

	fprintf(stdout, "OK\n");

	msg_free(msg);
	kill_free(kill_one);
	kill_free(kill_two);

	evrpc_pool_free(pool);
	evhttp_free(http);
}
