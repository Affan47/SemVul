cb_graph_size_changed (GocItem *item, GtkAllocation *allocation)
{
	GogRenderer *rend;
	GogGraph *graph;
	SheetObject *so = sheet_object_view_get_so (SHEET_OBJECT_VIEW (item->parent));
	PrintInformation *pi = so->sheet->print_info;
	double top, bottom, left, right, edge_to_below_header, edge_to_above_footer, w, h, x = 0., y = 0.;
	w = print_info_get_paper_width (pi, GTK_UNIT_POINTS);
	h = print_info_get_paper_height (pi, GTK_UNIT_POINTS);
	print_info_get_margins (pi, &top, &bottom, &left, &right, &edge_to_below_header, &edge_to_above_footer);
	w -= left + right;
	h -= edge_to_above_footer + edge_to_below_header;
	g_object_get (item, "renderer", &rend, NULL);
	g_object_get (rend, "model", &graph, NULL);
	gog_graph_set_size (graph, w, h);
	if (w / allocation->width > h / allocation->height) {
		h = allocation->width * h / w;
		w = allocation->width;
		y = (allocation->height - h) / 2.;
	} else {
		w = allocation->height * w / h;
		h = allocation->height;
		x = (allocation->width - w) / 2.;
	}
	goc_item_set (item, "x", x, "width", w, "y", y, "height", h, NULL);
	g_object_unref (graph);
	g_object_unref (rend);
}
