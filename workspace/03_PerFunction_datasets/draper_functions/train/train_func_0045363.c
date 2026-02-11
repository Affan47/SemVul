dump_packet_from(struct dump *dump, const struct gnutella_node *node)
{
	struct dump_header dh;

	g_assert(node != NULL);

	if (!dump_initialize(dump))
		return;

	if (!ipset_contains_addr(&dump_rx_addrs, node->addr, TRUE))
		return;

	dump_header_set(&dh, node);
	dump_append(dump, dh.data, sizeof dh.data);
	dump_append(dump, node->header, sizeof node->header);
	dump_append(dump, node->data, node->size);
	dump_flush(dump);
}
