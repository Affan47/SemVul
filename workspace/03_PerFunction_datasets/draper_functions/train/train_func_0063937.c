panel_widget_reparent (PanelWidget         *old_panel,
		       PanelWidget         *new_panel,
		       GtkWidget           *applet,
		       PanelObjectPackType  pack_type,
		       int                  pack_index)
{
	AppletData *ad;
	GtkWidget *focus_widget = NULL;
	AppletInfo* info;

	g_return_val_if_fail(PANEL_IS_WIDGET(old_panel), FALSE);
	g_return_val_if_fail(PANEL_IS_WIDGET(new_panel), FALSE);
	g_return_val_if_fail(GTK_IS_WIDGET(applet), FALSE);
	g_return_val_if_fail(pack_index>=0, FALSE);

	ad = g_object_get_data (G_OBJECT (applet), PANEL_APPLET_DATA);
	g_return_val_if_fail(ad!=NULL, FALSE);


	if (panel_toplevel_get_is_hidden (new_panel->toplevel))
		return FALSE;

	info = g_object_get_data (G_OBJECT (ad->applet), "applet_info");

	panel_widget_move_to_pack (new_panel, ad, pack_type, pack_index);


	gtk_widget_queue_resize (GTK_WIDGET (new_panel));
	gtk_widget_queue_resize (GTK_WIDGET (old_panel));

	panel_widget_reset_saved_focus (old_panel);
	if (gtk_container_get_focus_child (GTK_CONTAINER (old_panel)) == applet)
		focus_widget = gtk_window_get_focus (GTK_WINDOW (old_panel->toplevel));
	gtk_widget_reparent (applet, GTK_WIDGET (new_panel));

	if (info && info->type == PANEL_OBJECT_APPLET)
		panel_applet_frame_set_panel (PANEL_APPLET_FRAME (ad->applet), new_panel);

	if (gtk_widget_get_can_focus (GTK_WIDGET (new_panel)))
		gtk_widget_set_can_focus (GTK_WIDGET (new_panel), FALSE);
	if (focus_widget) {
		panel_widget_force_grab_focus (focus_widget);
	} else {
		gboolean return_val;

		g_signal_emit_by_name (applet, "focus",
				       GTK_DIR_TAB_FORWARD,
				       &return_val);
	}
 	gtk_window_present (GTK_WINDOW (new_panel->toplevel));

	gdk_flush();

	emit_applet_moved (new_panel, ad);

	return TRUE;
}
