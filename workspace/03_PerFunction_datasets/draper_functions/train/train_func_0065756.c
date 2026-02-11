out_ca_detail(ibnd_node_t * node, char *ca_prefix)
{
	char *node_type;

	switch (node->type) {
	case IB_NODE_CA:
		node_type = "Ca";
		break;
	case IB_NODE_ROUTER:
		node_type = "Rt";
		break;
	default:
		node_type = "???";
		break;
	}

	fprintf(f, "%s%s\t%d %s\t\t# \"%s\"", ca_prefix ? ca_prefix : "",
		node_type, node->numports, node_name(node),
		clean_nodedesc(node->nodedesc));
}
