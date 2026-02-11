rt_node_info_del(struct rt_node_info * ni)
{
	if (ni != NULL) {
		if (ni->nodename != NULL) {
			free(ni->nodename);
		}
		memset(ni, 0, sizeof(*ni));
		free(ni);
	}
}
