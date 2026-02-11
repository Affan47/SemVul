inv_display_err_button_release_event (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(INV_IS_DISPLAY_ERR(widget));

	if(INV_DISPLAY_ERR(widget)->active_dot == INV_DISPLAY_ERR_DOT_SOURCE
	|| INV_DISPLAY_ERR(widget)->active_dot == INV_DISPLAY_ERR_DOT_DEST) {
		INV_DISPLAY_ERR(widget)->active_dot= INV_DISPLAY_ERR_DOT_NONE;
		gtk_widget_set_state(widget,GTK_STATE_NORMAL);
		g_object_set(G_OBJECT(widget),"has-tooltip",TRUE,NULL);
		inv_display_err_paint(widget,INV_DISPLAY_ERR_DRAW_DATA);
	}
	return TRUE;
}
