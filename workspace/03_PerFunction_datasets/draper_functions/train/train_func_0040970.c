etfci_update (GnomeCanvasItem *item,
              const cairo_matrix_t *i2c,
              gint flags)
{
	ETableFieldChooserItem *etfci = E_TABLE_FIELD_CHOOSER_ITEM (item);
	gdouble x1, y1, x2, y2;

	if (GNOME_CANVAS_ITEM_CLASS (e_table_field_chooser_item_parent_class)->update)
		GNOME_CANVAS_ITEM_CLASS (e_table_field_chooser_item_parent_class)->update (
			item, i2c, flags);

	x1 = y1 = 0;
	x2 = etfci->width;
	y2 = etfci->height;

	gnome_canvas_matrix_transform_rect (i2c, &x1, &y1, &x2, &y2);

	if (item->x1 != x1 ||
	    item->y1 != y1 ||
	    item->x2 != x2 ||
	    item->y2 != y2)
		{
			gnome_canvas_request_redraw (
				item->canvas, item->x1,
				item->y1, item->x2, item->y2);
			item->x1 = x1;
			item->y1 = y1;
			item->x2 = x2;
			item->y2 = y2;

#if 0
			gnome_canvas_group_child_bounds (
				GNOME_CANVAS_GROUP (item->parent), item);
#endif
		}
	gnome_canvas_request_redraw (
		item->canvas, item->x1, item->y1, item->x2, item->y2);
}
