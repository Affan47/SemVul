button_clicked (GtkButton *button,
                EFilterDatespec *fds)
{
	EFilterDatespecPrivate *p = E_FILTER_DATESPEC_GET_PRIVATE (fds);
	GtkWidget *content_area;
	GtkWidget *toplevel;
	GtkDialog *dialog;
	GtkBuilder *builder;


	builder = gtk_builder_new ();
	e_load_ui_builder_definition (builder, "filter.ui");

	toplevel = e_builder_get_widget (builder, "filter_datespec");

	dialog = (GtkDialog *) gtk_dialog_new ();
	gtk_window_set_title (
		GTK_WINDOW (dialog),
		_("Select a time to compare against"));
	gtk_dialog_add_buttons (
		dialog,
		GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
		GTK_STOCK_OK, GTK_RESPONSE_OK,
		NULL);

	p->notebook_type = e_builder_get_widget (builder, "notebook_type");
	p->combobox_type = e_builder_get_widget (builder, "combobox_type");
	p->calendar_specify = e_builder_get_widget (builder, "calendar_specify");
	p->spin_relative = e_builder_get_widget (builder, "spin_relative");
	p->combobox_relative = e_builder_get_widget (builder, "combobox_relative");
	p->combobox_past_future = e_builder_get_widget (builder, "combobox_past_future");

	set_values (fds);

	g_signal_connect (
		p->combobox_type, "changed",
		G_CALLBACK (set_combobox_type), fds);
	g_signal_connect (
		p->combobox_relative, "changed",
		G_CALLBACK (set_combobox_relative), fds);
	g_signal_connect (
		p->combobox_past_future, "changed",
		G_CALLBACK (set_combobox_past_future), fds);

	content_area = gtk_dialog_get_content_area (dialog);
	gtk_box_pack_start (GTK_BOX (content_area), toplevel, TRUE, TRUE, 3);

	if (gtk_dialog_run (dialog) == GTK_RESPONSE_OK) {
		get_values (fds);
		set_button (fds);
	}

	gtk_widget_destroy ((GtkWidget *) dialog);
}
