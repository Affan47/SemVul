scif_get_node_ids(u16 *nodes, int len, u16 *self)
{
	int online = 0;
	int offset = 0;
	int node;

	if (!scif_is_mgmt_node())
		scif_get_node_info();

	*self = scif_info.nodeid;
	mutex_lock(&scif_info.conflock);
	len = min_t(int, len, scif_info.total);
	for (node = 0; node <= scif_info.maxid; node++) {
		if (_scifdev_alive(&scif_dev[node])) {
			online++;
			if (offset < len)
				nodes[offset++] = node;
		}
	}
	dev_dbg(scif_info.mdev.this_device,
		"SCIFAPI get_node_ids total %d online %d filled in %d nodes\n",
		scif_info.total, online, offset);
	mutex_unlock(&scif_info.conflock);

	return online;
}
