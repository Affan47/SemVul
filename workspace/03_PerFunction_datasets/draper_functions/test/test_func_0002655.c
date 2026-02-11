rb_match_ip(rb_patricia_tree_t *tree, struct sockaddr *ip)
{
	rb_prefix_t *prefix;
	rb_patricia_node_t *node;
	void *ipptr;
	unsigned int len;
	int family;
#ifndef RB_IPV6
	len = 32;
	family = AF_INET;
	ipptr = &((struct sockaddr_in *)ip)->sin_addr;
#else
	if(ip->sa_family == AF_INET6)
	{
		len = 128;
		family = AF_INET6;
		ipptr = &((struct sockaddr_in6 *)ip)->sin6_addr;
	}
	else
	{
		len = 32;
		family = AF_INET;
		ipptr = &((struct sockaddr_in *)ip)->sin_addr;
	}
#endif

	if((prefix = New_Prefix(family, ipptr, len)) != NULL)
	{
		node = rb_patricia_search_best(tree, prefix);
		Deref_Prefix(prefix);
		return (node);
	}
	return NULL;
}
