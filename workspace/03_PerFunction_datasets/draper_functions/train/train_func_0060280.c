gth_grid_view_item_is_inside_area (GthGridViewItem *item,
				   int              x1,
				   int              y1,
				   int              x2,
				   int              y2)
{
	GdkRectangle area;
	GdkRectangle item_area;
	double       x_ofs;
	double       y_ofs;

	if ((x1 == x2) && (y1 == y2))
		return FALSE;

	area.x = x1;
	area.y = y1;
	area.width = x2 - x1;
	area.height = y2 - y1;

	item_area = item->area;
	x_ofs = item_area.width / 6;
	y_ofs = item_area.height / 6;
	item_area.x      += x_ofs;
	item_area.y      += y_ofs;
	item_area.width  -= x_ofs * 2;
	item_area.height -= y_ofs * 2;

	return gdk_rectangle_intersect (&item_area, &area, NULL);
}
