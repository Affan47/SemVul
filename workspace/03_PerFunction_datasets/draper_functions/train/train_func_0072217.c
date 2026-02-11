on_win_main_delete_event (GtkWidget *w, GdkEventButton *event, GbemolApp* data)
{
	if (gbemol_cfg_get_bool("app", "close-tray") && gbemol_cfg_get_bool("app", "status-icon"))
	{
		gtk_widget_hide (data->priv->win_main);
		gbemol_cfg_set_bool("win_main", "visible", TRUE);
		return TRUE;
	}
	else
	{
		g_object_unref (G_OBJECT(data));
		gbemol_app_destroy (data);
		gtk_main_quit ();
		return FALSE;
	}
}
