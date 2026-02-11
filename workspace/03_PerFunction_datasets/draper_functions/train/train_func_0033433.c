add_reject(struct Client *client_p)
{
	rb_patricia_node_t *pnode;
	reject_t *rdata;


	if(ConfigFileEntry.reject_after_count == 0 || ConfigFileEntry.reject_duration == 0)
		return;

	if((pnode =
	    rb_match_ip(reject_tree, (struct sockaddr *)&client_p->localClient->ip)) != NULL)
	{
		rdata = pnode->data;
		rdata->time = rb_current_time();
		rdata->count++;
	}
	else
	{
		int bitlen = 32;
#ifdef RB_IPV6
		if(GET_SS_FAMILY(&client_p->localClient->ip) == AF_INET6)
			bitlen = 128;
#endif
		pnode = make_and_lookup_ip(reject_tree,
					   (struct sockaddr *)&client_p->localClient->ip, bitlen);
		pnode->data = rdata = rb_malloc(sizeof(reject_t));
		rb_dlinkAddTail(pnode, &rdata->rnode, &reject_list);
		rdata->time = rb_current_time();
		rdata->count = 1;
	}
}
