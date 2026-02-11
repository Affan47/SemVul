visibility_graph(pf_state_t *s)


{
	polygon_t *polygon;

	LIST_FOREACH(polygon, &s->polygons, entries) {
		vertex_t *vertex;

		CLIST_FOREACH(vertex, &polygon->vertices, entries)
			visible_vertices(s, vertex);
	}
}
