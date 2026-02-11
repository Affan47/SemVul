dlmc_lockspace_nodes(char *name, int type, int max, int *count,
			 struct dlmc_node *nodes)
{
	struct dlmc_header h, *rh;
	char *reply;
	int reply_len;
	int fd, rv, result, node_count;

	init_header(&h, DLMC_CMD_LOCKSPACE_NODES, name, 0);
	h.option = type;
	h.data = max;

	reply_len = sizeof(struct dlmc_header) +
		    (max * sizeof(struct dlmc_node));
	reply = malloc(reply_len);
	if (!reply) {
		rv = -1;
		goto out;
	}
	memset(reply, 0, reply_len);

	fd = do_connect(DLMC_QUERY_SOCK_PATH);
	if (fd < 0) {
		rv = fd;
		goto out;
	}

	rv = do_write(fd, &h, sizeof(h));
	if (rv < 0)
		goto out_close;


	do_read(fd, reply, reply_len);

	rh = (struct dlmc_header *)reply;
	result = rh->data;
	if (result < 0 && result != -E2BIG) {
		rv = result;
		goto out_close;
	}

	if (result == -E2BIG) {
		*count = -E2BIG;
		node_count = max;
	} else {
		*count = result;
		node_count = result;
	}
	rv = 0;

	memcpy(nodes, (char *)reply + sizeof(struct dlmc_header),
	       node_count * sizeof(struct dlmc_node));
 out_close:
	close(fd);
 out:
	return rv;
}
