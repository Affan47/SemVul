eel_canvas_draw (GtkWidget *widget, cairo_t *cr)
{
	EelCanvas *canvas = EEL_CANVAS (widget);
        GdkWindow *bin_window;
        cairo_region_t *region;

        if (!gdk_cairo_get_clip_rectangle (cr, NULL))
                return FALSE;

        bin_window = gtk_layout_get_bin_window (GTK_LAYOUT (widget));

	if (!gtk_cairo_should_draw_window (cr, bin_window))
		return FALSE;

	cairo_save (cr);

        gtk_cairo_transform_to_window (cr, widget, bin_window);

        region = eel_cairo_get_clip_region (cr);
        if (region == NULL) {
		cairo_restore (cr);
                return FALSE;
	}

#ifdef VERBOSE
	g_print ("Draw\n");
#endif

	if (canvas->idle_id) {
		g_source_remove (canvas->idle_id);
		canvas->idle_id = 0;
	}
	if (canvas->need_update) {
		g_return_val_if_fail (!canvas->doing_update, FALSE);

		canvas->doing_update = TRUE;
		eel_canvas_item_invoke_update (canvas->root, 0, 0, 0);

		g_return_val_if_fail (canvas->doing_update, FALSE);

		canvas->doing_update = FALSE;

		canvas->need_update = FALSE;
	}


	g_signal_emit (G_OBJECT (canvas), canvas_signals[DRAW_BACKGROUND], 0,
                       cr);

	if (canvas->root->flags & EEL_CANVAS_ITEM_MAPPED)
		EEL_CANVAS_ITEM_GET_CLASS (canvas->root)->draw (canvas->root, cr, region);

	cairo_restore (cr);


        if (GTK_WIDGET_CLASS (canvas_parent_class)->draw)
                GTK_WIDGET_CLASS (canvas_parent_class)->draw (widget, cr);

        cairo_region_destroy (region);
	return FALSE;
}
