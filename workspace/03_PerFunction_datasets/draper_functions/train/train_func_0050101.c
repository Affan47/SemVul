gitg_utils_restore_pane_position (GtkPaned *paned, gint position, gboolean reversed)
{
	g_return_if_fail (GTK_IS_PANED (paned));

	if (gtk_widget_get_mapped (GTK_WIDGET (paned)))
	{
		paned_set_position (paned, position, reversed);

		return;
	}

	PanedRestoreInfo *info = g_slice_new (PanedRestoreInfo);
	info->position = position;
	info->reversed = reversed;

	g_signal_connect_data (paned,
	                       "map",
	                       G_CALLBACK (on_paned_mapped),
	                       info,
	                       (GClosureNotify)free_paned_restore_info,
	                       G_CONNECT_AFTER);
}
