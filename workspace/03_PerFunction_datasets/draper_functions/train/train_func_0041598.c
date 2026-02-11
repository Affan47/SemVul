nautilus_canvas_item_get_drag_surface (NautilusCanvasItem *item)
{
	cairo_surface_t *surface;
	EelCanvas *canvas;
	int width, height;
	int pix_width, pix_height;
	int item_offset_x, item_offset_y;
	EelIRect icon_rect;
	double item_x, item_y;
	cairo_t *cr;
	GtkStyleContext *context;
	cairo_surface_t *drag_surface;

	g_return_val_if_fail (NAUTILUS_IS_CANVAS_ITEM (item), NULL);

	canvas = EEL_CANVAS_ITEM (item)->canvas;
	context = gtk_widget_get_style_context (GTK_WIDGET (canvas));

	gtk_style_context_save (context);
	gtk_style_context_add_class (context, "nautilus-canvas-item");


	eel_canvas_world_to_window (canvas,
				    item->details->x, item->details->y,
				    &item_x, &item_y);

	item_offset_x = item_x - EEL_CANVAS_ITEM (item)->x1;
	item_offset_y = item_y - EEL_CANVAS_ITEM (item)->y1;


	width = EEL_CANVAS_ITEM (item)->x2 - EEL_CANVAS_ITEM (item)->x1;
	height = EEL_CANVAS_ITEM (item)->y2 - EEL_CANVAS_ITEM (item)->y1;

        surface = gdk_window_create_similar_surface (gtk_widget_get_window (GTK_WIDGET (canvas)),
						     CAIRO_CONTENT_COLOR_ALPHA,
						     width, height);
	cr = cairo_create (surface);

	drag_surface = map_surface (item);
	gtk_render_icon_surface (context, cr, drag_surface,
				 item_offset_x, item_offset_y);
	cairo_surface_destroy (drag_surface);

	get_scaled_icon_size (item, &pix_width, &pix_height);

	icon_rect.x0 = item_offset_x;
	icon_rect.y0 = item_offset_y;
	icon_rect.x1 = item_offset_x + pix_width;
	icon_rect.y1 = item_offset_y + pix_height;

	draw_embedded_text (item, cr,
			    item_offset_x, item_offset_y);
	draw_label_text (item, cr, icon_rect);
	cairo_destroy (cr);

	gtk_style_context_restore (context);

	return surface;
}
