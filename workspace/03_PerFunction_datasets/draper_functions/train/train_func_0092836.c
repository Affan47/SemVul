nm_utils_ip4_routes_to_gvalue (GSList *list, GValue *value)
{
	GPtrArray *routes;
	GSList *iter;

	routes = g_ptr_array_new ();

	for (iter = list; iter; iter = iter->next) {
		NMIP4Route *route = (NMIP4Route *) iter->data;
		GArray *array;
		guint32 tmp;

		array = g_array_sized_new (FALSE, TRUE, sizeof (guint32), 3);

		tmp = nm_ip4_route_get_dest (route);
		g_array_append_val (array, tmp);

		tmp = nm_ip4_route_get_prefix (route);
		g_array_append_val (array, tmp);

		tmp = nm_ip4_route_get_next_hop (route);
		g_array_append_val (array, tmp);

		tmp = nm_ip4_route_get_metric (route);
		g_array_append_val (array, tmp);

		g_ptr_array_add (routes, array);
	}

	g_value_take_boxed (value, routes);
}
