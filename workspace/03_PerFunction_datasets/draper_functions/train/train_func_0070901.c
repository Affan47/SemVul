nemo_icon_canvas_item_draw (EelCanvasItem *item,
                                cairo_t *cr,
                                cairo_region_t *region)
{
	NemoIconContainer *container;
	NemoIconCanvasItem *icon_item;
	NemoIconCanvasItemDetails *details;
	EelIRect icon_rect;
	GdkPixbuf *temp_pixbuf;
	GtkStyleContext *context;

	container = NEMO_ICON_CONTAINER (item->canvas);
	icon_item = NEMO_ICON_CANVAS_ITEM (item);
	details = icon_item->details;


     	if (details->pixbuf == NULL) {
		return;
	}

	context = gtk_widget_get_style_context (GTK_WIDGET (container));
	gtk_style_context_save (context);
	if (gtk_style_context_has_class (context, "nemo-canvas-item")) {
		gtk_style_context_add_class (context, "nemo-canvas-item");
	}
	else {
		gtk_style_context_add_class (context, "nautilus-canvas-item");
	}

	icon_rect = icon_item->details->canvas_rect;
	temp_pixbuf = map_pixbuf (icon_item);

	gtk_render_icon (context, cr,
			 temp_pixbuf,
			 icon_rect.x0, icon_rect.y0);
	g_object_unref (temp_pixbuf);

	draw_embedded_text (icon_item, cr, icon_rect.x0, icon_rect.y0);


	draw_stretch_handles (icon_item, cr, &icon_rect);


	draw_label_text (icon_item, cr, icon_rect);

	gtk_style_context_restore (context);
}
