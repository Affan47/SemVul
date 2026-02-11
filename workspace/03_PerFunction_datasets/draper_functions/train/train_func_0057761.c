cb_treeview_button_press (GtkWidget *treeview,
			  GdkEventButton *event,
			  StfDialogData *pagedata)
{
	if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
		int dx, col;
		stf_preview_find_column (pagedata->format.renderdata, (int)event->x, &col, &dx);
		activate_column (pagedata, col);
		return TRUE;
	} else if (event->type == GDK_BUTTON_PRESS && event->button == 3) {
		int dx, col;
		stf_preview_find_column (pagedata->format.renderdata, (int)event->x, &col, &dx);
		activate_column (pagedata, col);
		format_context_menu (pagedata, event, col);
		return TRUE;
	}

	return FALSE;
}
