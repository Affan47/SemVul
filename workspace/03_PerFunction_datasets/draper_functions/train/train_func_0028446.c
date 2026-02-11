convert_polygon(state_t *s, reg_t polygon)


{
	int i;
	reg_t points = GET_SEL32(polygon, points);
	int size = KP_UINT(GET_SEL32(polygon, size));
	unsigned char *list = kernel_dereference_bulk_pointer(s, points, size * POLY_POINT_SIZE);
	polygon_t *poly = polygon_new(KP_UINT(GET_SEL32(polygon, type)));
	int is_reg_t = polygon_is_reg_t(list, size);

	for (i = 0; i < size; i++) {
		vertex_t *vertex = vertex_new(read_point(list, is_reg_t, i));
		CLIST_INSERT_HEAD(&poly->vertices, vertex, entries);
	}

	fix_vertex_order(poly);

	return poly;
}
