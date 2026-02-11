make_client(struct Client *from)
{
	struct Client *client_p = NULL;
	struct LocalUser *localClient;

	client_p = rb_bh_alloc(client_heap);

	if(from == NULL)
	{
		client_p->from = client_p;

		localClient = rb_bh_alloc(lclient_heap);
		SetMyConnect(client_p);
		client_p->localClient = localClient;

		client_p->localClient->lasttime = client_p->localClient->firsttime = rb_current_time();

		client_p->localClient->F = NULL;

		client_p->preClient = rb_bh_alloc(pclient_heap);;


		rb_dlinkAdd(client_p, &client_p->localClient->tnode, &unknown_list);
	}
	else
	{
		client_p->localClient = NULL;
		client_p->preClient = NULL;
		client_p->from = from;
	}

	SetUnknown(client_p);
	strcpy(client_p->username, "unknown");

	return client_p;
}
