on_gm_world_view_world_active_changed(GmWorld *world, GParamSpec *pspec,
		GmWorldView *view) {
	if (gm_world_active(world)) {
		gtk_widget_grab_focus(GTK_WIDGET(view->priv->text_view_input));
	}
}
