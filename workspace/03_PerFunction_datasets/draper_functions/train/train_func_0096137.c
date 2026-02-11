on_gm_mcp_userlist_view_weak_notify(gpointer data, GObject *obj) {
	GmMcpUserlistView *view = (GmMcpUserlistView *)(data);
	GtkWidget *vbox;
	GList *children;

	if (GM_IS_WORLD_VIEW(view->view)) {
		gtk_widget_destroy(GTK_WIDGET(view->scrolled_window));
		gtk_widget_destroy(view->label);

		vbox = gtk_paned_get_child2(GTK_PANED(gm_world_view_hpaned(
				view->view)));

		if (vbox != NULL) {
			children = gtk_container_get_children(GTK_CONTAINER(vbox));

			if (children == NULL) {
				gtk_widget_destroy(vbox);
			}

			g_list_free(children);
		}
	}

	g_object_unref(G_OBJECT(view->store));
	g_object_unref(G_OBJECT(view->model));

	g_signal_handlers_disconnect_by_func(gm_app_options(gm_app_instance()),
			G_CALLBACK(on_gm_mcp_userlist_view_option_changed), view);

	g_free(data);
}
