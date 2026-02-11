mg_create_tabmenu(window_t *sess, GdkEventButton *event, chan *ch) {
	GtkWidget *menu, *item;
	char buf[256];

	menu = gtk_menu_new();

	if (sess) {
		const char *w_target = gtk_window_target(sess);
		char *target = g_markup_escape_text(w_target[0] ? w_target : "<none>", -1);

		const char *w_session = (sess && sess->session) ? sess->session->uid : NULL;
		char *session = w_session ? g_markup_escape_text(w_session, -1) : NULL;

		snprintf(buf, sizeof(buf), "<span foreground=\"#3344cc\"><b>%s %s</b></span>", target, session ? session : "");
		g_free(target);
		g_free(session);

		item = gtk_menu_item_new_with_label("");
		gtk_label_set_markup(GTK_LABEL(GTK_BIN(item)->child), buf);
		gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
		gtk_widget_show(item);


		item = gtk_menu_item_new();
		gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
		gtk_widget_show(item);

#if 0

		mg_create_alertmenu (sess, menu);


		mg_create_perchannelmenu (sess, menu);


		menu_quick_item (0, 0, menu, XCMENU_SHADED, 0, 0);

		if (sess->type == SESS_CHANNEL)
			menu_addfavoritemenu (sess->server, menu, sess->channel);
#endif
	}

	mg_create_icon_item(_("_Close"), GTK_STOCK_CLOSE, menu, mg_destroy_tab_cb, ch);
	mg_create_icon_item(_("_Detach"), GTK_STOCK_REDO, menu, mg_detach_tab_cb, ch);
#if 0

	if (sess && tabmenu_list)
		menu_create(menu, tabmenu_list, sess->channel, FALSE);
	menu_add_plugin_items(menu, "\x4$TAB", sess->channel);
#endif

	if (event->window)
		gtk_menu_set_screen(GTK_MENU(menu), gdk_drawable_get_screen(event->window));
	g_object_ref(menu);
	g_object_ref_sink(menu);
	g_object_unref(menu);
	g_signal_connect(G_OBJECT(menu), "selection-done", G_CALLBACK(mg_menu_destroy), NULL);
	gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL, 0, event->time);
}
