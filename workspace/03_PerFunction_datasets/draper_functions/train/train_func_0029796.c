node_desc(ib_portid_t * dest, char **argv, int argc)
{
	int node_type, l;
	uint64_t node_guid;
	char nd[IB_SMP_DATA_SIZE] = { 0 };
	uint8_t data[IB_SMP_DATA_SIZE] = { 0 };
	char dots[128];
	char *nodename = NULL;

	if (!smp_query_via(data, dest, IB_ATTR_NODE_INFO, 0, 0, srcport))
		return "node info query failed";

	mad_decode_field(data, IB_NODE_TYPE_F, &node_type);
	mad_decode_field(data, IB_NODE_GUID_F, &node_guid);

	if (!smp_query_via(nd, dest, IB_ATTR_NODE_DESC, 0, 0, srcport))
		return "node desc query failed";

	nodename = remap_node_name(node_name_map, node_guid, nd);

	l = strlen(nodename);
	if (l < 32) {
		memset(dots, '.', 32 - l);
		dots[32 - l] = '\0';
	} else {
		dots[0] = '.';
		dots[1] = '\0';
	}

	printf("Node Description:%s%s\n", dots, nodename);
	free(nodename);
	return 0;
}
