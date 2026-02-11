list_node(ibnd_node_t * node, void *user_data)
{
	char *node_type;
	char *nodename = remap_node_name(node_name_map, node->guid,
					 node->nodedesc);

	switch (node->type) {
	case IB_NODE_SWITCH:
		node_type = "Switch";
		break;
	case IB_NODE_CA:
		node_type = "Ca";
		break;
	case IB_NODE_ROUTER:
		node_type = "Router";
		break;
	default:
		node_type = "???";
		break;
	}
	fprintf(f,
		"%s\t : 0x%016" PRIx64
		" ports %d devid 0x%x vendid 0x%x \"%s\"\n", node_type,
		node->guid, node->numports, mad_get_field(node->info, 0,
							  IB_NODE_DEVID_F),
		mad_get_field(node->info, 0, IB_NODE_VENDORID_F), nodename);

	free(nodename);
}
