print_node(ibnd_node_t * node, void *user_data)
{
	int i = 0;
	int head_print = 0;
	char *out_prefix = (char *)user_data;

	for (i = 1; i <= node->numports; i++) {
		ibnd_port_t *port = node->ports[i];
		if (!port)
			continue;
		if (!down_links_only ||
		    mad_get_field(port->info, 0,
				  IB_PORT_STATE_F) == IB_LINK_DOWN) {
			print_node_header(node, &head_print, out_prefix);
			print_port(node, port, out_prefix);
		}
	}
}
