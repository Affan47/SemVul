rehash_nickdelay(struct Client *source_p)
{
	struct nd_entry *nd;
	rb_dlink_node *ptr;
	rb_dlink_node *safe_ptr;

	sendto_realops_snomask(SNO_GENERAL, L_ALL,
			     "%s is clearing the nick delay table",
			     get_oper_name(source_p));
	if (!MyConnect(source_p))
		remote_rehash_oper_p = source_p;

	RB_DLINK_FOREACH_SAFE(ptr, safe_ptr, nd_list.head)
	{
		nd = ptr->data;

		free_nd_entry(nd);
	}
}
