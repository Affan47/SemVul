get_routing_data(void *n)
{
	g_assert(n != NULL);

	switch (((struct node_magic *) n)->magic) {
	case NODE_MAGIC:
		{
			struct gnutella_node *gn = n;
			struct routing_udp_node *un;

			if (!NODE_IS_UDP(gn))
				return gn->routing_data;


			un = route_get_udp(gn);
			return un->routing_data;
		}
	case NODE_UDP_MAGIC:
		return ((struct routing_udp_node *) n)->routing_data;
	}
	g_assert_not_reached();
}
