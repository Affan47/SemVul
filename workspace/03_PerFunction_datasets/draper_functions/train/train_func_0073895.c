_goc_item_transform (GocItem const *item, cairo_t *cr, gboolean scaled)
{
	cairo_matrix_t m = item->transform, buf,
		sc = {item->canvas->pixels_per_unit, 0., 0., item->canvas->pixels_per_unit, 0., 0.};
	while ((item = GOC_ITEM (item->parent)))
		if (item->transformed) {
			cairo_matrix_multiply (&buf, &m, &item->transform);
			m = buf;
		}
	if (scaled) {
		cairo_matrix_multiply (&buf, &m, &sc);
		m = buf;
	}
	cairo_transform (cr, &m);
}
