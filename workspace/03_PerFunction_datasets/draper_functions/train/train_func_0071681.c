abort_blacklist_queries(struct Client *client_p)
{
	rb_dlink_node *ptr, *next_ptr;
	struct BlacklistClient *blcptr;

	if (client_p->preClient == NULL)
		return;
	RB_DLINK_FOREACH_SAFE(ptr, next_ptr, client_p->preClient->dnsbl_queries.head)
	{
		blcptr = ptr->data;
		rb_dlinkDelete(&blcptr->node, &client_p->preClient->dnsbl_queries);
		unref_blacklist(blcptr->blacklist);
		delete_resolver_queries(&blcptr->dns_query);
		rb_free(blcptr);
	}
}
