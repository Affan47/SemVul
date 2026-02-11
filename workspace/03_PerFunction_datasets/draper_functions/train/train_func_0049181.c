tree_canvas_reflow_idle (ETree *tree)
{
	gdouble height, width;
	gdouble oldheight, oldwidth;
	GtkAllocation allocation;
	GtkWidget *widget;

	widget = GTK_WIDGET (tree->priv->table_canvas);
	gtk_widget_get_allocation (widget, &allocation);

	g_object_get (
		tree->priv->item,
		"height", &height, "width", &width, NULL);

	height = MAX ((gint) height, allocation.height);
	width = MAX ((gint) width, allocation.width);


	gnome_canvas_get_scroll_region (
		GNOME_CANVAS (tree->priv->table_canvas),
		NULL, NULL, &oldwidth, &oldheight);

	if (oldwidth != width - 1 ||
	    oldheight != height - 1) {
		gnome_canvas_set_scroll_region (
			GNOME_CANVAS (tree->priv->table_canvas),
			0, 0, width - 1, height - 1);
		set_header_canvas_width (tree);
	}

	tree->priv->reflow_idle_id = 0;

	if (tree->priv->show_cursor_after_reflow) {
		tree->priv->show_cursor_after_reflow = FALSE;
		scroll_to_cursor (tree);
	}

	return FALSE;
}
