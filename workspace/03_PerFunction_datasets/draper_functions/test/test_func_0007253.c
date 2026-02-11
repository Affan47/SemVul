write_maxconn(struct file *file, char *buf, size_t size)
{
	char *mesg = buf;
	struct nfsd_net *nn = net_generic(netns(file), nfsd_net_id);
	unsigned int maxconn = nn->max_connections;

	if (size > 0) {
		int rv = get_uint(&mesg, &maxconn);

		if (rv)
			return rv;
		nn->max_connections = maxconn;
	}

	return scnprintf(buf, SIMPLE_TRANSACTION_LIMIT, "%u\n", maxconn);
}
