DocumentLocationDialog(Gtk::Window& parent,
                                                      InfGtkBrowserModel* m):
	Gtk::Dialog("", parent),
	m_box(false, 6),
	m_name_box(false, 6),
	m_name_label(_("Document Name:"), GtkCompat::ALIGN_RIGHT),
	m_location_label("", GtkCompat::ALIGN_LEFT),
	m_filter_model(inf_gtk_browser_model_filter_new(m)),
	m_view(INF_GTK_BROWSER_VIEW(inf_gtk_browser_view_new_with_model(
		INF_GTK_BROWSER_MODEL(m_filter_model))))
{

	set_single_document_mode();

	m_name_label.show();
	m_name_entry.show();
	m_name_entry.set_activates_default(true);
	m_location_label.show();
	gtk_widget_show(GTK_WIDGET(m_view));

	gtk_container_add(GTK_CONTAINER(m_scroll.gobj()), GTK_WIDGET(m_view));
	m_scroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	m_scroll.set_shadow_type(Gtk::SHADOW_IN);
	m_scroll.show();

	m_name_box.pack_start(m_name_label, Gtk::PACK_SHRINK);
	m_name_box.pack_start(m_name_entry, Gtk::PACK_EXPAND_WIDGET);
	m_name_box.show();

	m_box.pack_start(m_name_box, Gtk::PACK_SHRINK);
	m_box.pack_start(m_location_label, Gtk::PACK_SHRINK);
	m_box.pack_start(m_scroll, Gtk::PACK_EXPAND_WIDGET);
	m_box.show();

	g_signal_connect(m_view, "selection-changed",
	                 G_CALLBACK(on_selection_changed_static), this);
	g_signal_connect(m_filter_model, "row-changed",
	                 G_CALLBACK(on_row_changed_static), this);


	gtk_tree_model_filter_set_visible_func(
		GTK_TREE_MODEL_FILTER(m_filter_model),
		filter_visible_func_static, this, NULL);


	gtk_tree_model_filter_refilter(GTK_TREE_MODEL_FILTER(m_filter_model));

	get_vbox()->pack_start(m_box, Gtk::PACK_EXPAND_WIDGET);

	add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_ACCEPT);

	set_response_sensitive(Gtk::RESPONSE_ACCEPT, false);
	set_default_response(Gtk::RESPONSE_ACCEPT);
	set_default_size(-1, 480);
	set_border_width(12);
}
