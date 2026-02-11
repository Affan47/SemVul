cb_check_resize (GtkPaned *p, G_GNUC_UNUSED GtkAllocation *allocation,
		 SheetControlGUI *scg)
{
	gboolean const vert = (p == scg->vpane);
	gint max, pos = vert ? scg->vpos : scg->hpos;

	g_object_get (G_OBJECT (p), "max-position", &max, NULL);
	if (pos > max)
		pos = max;

	if (gtk_paned_get_position (p) != pos) {
		g_signal_handlers_block_by_func
			(G_OBJECT (p),
			 G_CALLBACK (cb_resize_pane_motion), scg);
		gtk_paned_set_position (p, pos);
		g_signal_handlers_unblock_by_func
			(G_OBJECT (p),
			 G_CALLBACK (cb_resize_pane_motion), scg);
	}
}
