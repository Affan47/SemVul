e_reflow_point (GnomeCanvasItem *item,
                gdouble x,
                gdouble y,
                gint cx,
                gint cy)
{
	GnomeCanvasItem *child = NULL;

	if (GNOME_CANVAS_ITEM_CLASS (e_reflow_parent_class)->point)
		child = GNOME_CANVAS_ITEM_CLASS (e_reflow_parent_class)->point (item, x, y, cx, cy);

	return child ? child : item;
#if 0
	if (y >= E_REFLOW_BORDER_WIDTH && y <= reflow->height - E_REFLOW_BORDER_WIDTH) {
		gfloat n_x;
		n_x = x;
		n_x += E_REFLOW_BORDER_WIDTH + E_REFLOW_DIVIDER_WIDTH;
		n_x = fmod (n_x, (reflow->column_width + E_REFLOW_FULL_GUTTER));
		if (n_x < E_REFLOW_FULL_GUTTER) {
			*actual_item = item;
			return 0;
		}
	}
	return distance;
#endif
}
