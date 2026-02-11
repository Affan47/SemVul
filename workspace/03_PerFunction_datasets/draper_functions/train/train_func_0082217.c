devhelp_plugin_init_webkit(DevhelpPlugin *self)
{
	GtkWidget *vbox, *toolbar;
	GtkToolItem *btn_zoom_in, *btn_zoom_out, *tb_sep;
	GtkScrolledWindow *webview_sw;
	DevhelpPluginPrivate *p;

	g_return_if_fail(self != NULL);

	p = self->priv;

	p->webview = webkit_web_view_new();

	webview_sw = GTK_SCROLLED_WINDOW(gtk_scrolled_window_new(NULL, NULL));
	gtk_scrolled_window_set_policy(webview_sw, GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type(webview_sw, GTK_SHADOW_ETCHED_IN);
	gtk_container_add(GTK_CONTAINER(webview_sw), p->webview);

	gtk_widget_show_all(GTK_WIDGET(webview_sw));

	vbox = gtk_vbox_new(FALSE, 0);
	toolbar = gtk_toolbar_new();

	p->btn_back = gtk_tool_button_new_from_stock(GTK_STOCK_GO_BACK);
	p->btn_forward = gtk_tool_button_new_from_stock(GTK_STOCK_GO_FORWARD);
	btn_zoom_in = gtk_tool_button_new_from_stock(GTK_STOCK_ZOOM_IN);
	btn_zoom_out = gtk_tool_button_new_from_stock(GTK_STOCK_ZOOM_OUT);
	tb_sep = gtk_separator_tool_item_new();

	gtk_widget_set_tooltip_text(GTK_WIDGET(p->btn_back), _("Go back one page"));
	gtk_widget_set_tooltip_text(GTK_WIDGET(p->btn_forward), _("Go forward one page"));
	gtk_widget_set_tooltip_text(GTK_WIDGET(btn_zoom_in), _("Zoom in"));
	gtk_widget_set_tooltip_text(GTK_WIDGET(btn_zoom_out), _("Zoom out"));

	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), p->btn_back, -1);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), p->btn_forward, -1);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tb_sep, -1);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), btn_zoom_in, -1);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), btn_zoom_out, -1);

	gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(webview_sw), TRUE, TRUE, 0);

	gtk_widget_show_all(vbox);
	p->webview_tab = vbox;
	devhelp_plugin_set_webview_location(self, DEVHELP_PLUGIN_WEBVIEW_LOCATION_MAIN_NOTEBOOK);

	g_signal_connect(p->btn_back, "clicked", G_CALLBACK(on_back_button_clicked), self);
	g_signal_connect(p->btn_forward, "clicked", G_CALLBACK(on_forward_button_clicked), self);
	g_signal_connect(btn_zoom_in, "clicked", G_CALLBACK(on_zoom_in_button_clicked), self);
	g_signal_connect(btn_zoom_out, "clicked", G_CALLBACK(on_zoom_out_button_clicked), self);

	g_signal_connect(WEBKIT_WEB_VIEW(p->webview), "document-load-finished", G_CALLBACK(on_document_load_finished), self);
	g_signal_connect(WEBKIT_WEB_VIEW(p->webview), "notify::uri", G_CALLBACK(on_uri_changed_notify), self);
	g_signal_connect(WEBKIT_WEB_VIEW(p->webview), "notify::load-status", G_CALLBACK(on_load_status_changed_notify), self);

	devhelp_plugin_set_webview_uri(self, NULL);
}
