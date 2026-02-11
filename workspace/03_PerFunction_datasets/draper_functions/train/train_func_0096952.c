allocate_callback (GtkWidget *canvas, GtkAllocation *allocation, ETableFieldChooser *etfc)
{
	gdouble height;
	etfc->last_alloc = *allocation;
	gnome_canvas_item_set (
		etfc->item,
		"width", (gdouble) allocation->width,
		NULL);
	g_object_get (
		etfc->item,
		"height", &height,
		NULL);
	height = MAX (height, allocation->height);
	gnome_canvas_set_scroll_region (GNOME_CANVAS (etfc->canvas), 0, 0, allocation->width - 1, height - 1);
	gnome_canvas_item_set (
		etfc->rect,
		"x2", (gdouble) allocation->width,
		"y2", (gdouble) height,
		NULL);
	ensure_nonzero_step_increments (etfc);
}
