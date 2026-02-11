ctl_byname(const char *name, void *oldp, size_t *oldlenp, void *newp,
    size_t newlen)
{
	int ret;
	size_t depth;
	ctl_node_t const *nodes[CTL_MAX_DEPTH];
	size_t mib[CTL_MAX_DEPTH];
	const ctl_named_node_t *node;

	if (ctl_initialized == false && ctl_init()) {
		ret = EAGAIN;
		goto label_return;
	}

	depth = CTL_MAX_DEPTH;
	ret = ctl_lookup(name, nodes, mib, &depth);
	if (ret != 0)
		goto label_return;

	node = ctl_named_node(nodes[depth-1]);
	if (node != NULL && node->ctl)
		ret = node->ctl(mib, depth, oldp, oldlenp, newp, newlen);
	else {

		ret = ENOENT;
	}

label_return:
	return(ret);
}
