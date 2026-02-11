ecb_style_set (ECanvasBackground *ecb,
               GtkStyle *previous_style)
{
	GnomeCanvasItem *item = GNOME_CANVAS_ITEM (ecb);

	if (gtk_widget_get_realized (GTK_WIDGET (item->canvas)))
		gnome_canvas_item_request_update (GNOME_CANVAS_ITEM (ecb));
}
