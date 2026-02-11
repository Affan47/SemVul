gtk_progress_dialog_new(GtkWindow* parent)
{
	GtkProgressDialog* dialog;
	GtkProgressDialogPrivate* priv;

	dialog = g_object_new (GTK_TYPE_PROGRESS_DIALOG, NULL);

	priv = GTK_PROGRESS_DIALOG_PRIVATE(dialog);

	gtk_window_set_transient_for (GTK_WINDOW(dialog), GTK_WINDOW(parent));
	gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);
	gtk_window_set_default_size (GTK_WINDOW(dialog), 480, -1);
	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);


	GtkWidget* vbox;
	vbox = gtk_vbox_new(FALSE, 5);
	gtk_container_set_border_width (GTK_CONTAINER(vbox), 10);

	priv->title_widget = gtk_label_new("");
	gtk_misc_set_alignment (GTK_MISC(priv->title_widget), 0.00F, 0.50F);
	gtk_box_pack_start (GTK_BOX(vbox), priv->title_widget, FALSE, FALSE, 0);

	priv->progress_widget = gtk_progress_bar_new();
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(priv->progress_widget), 0.0);
	gtk_progress_bar_set_text (GTK_PROGRESS_BAR(priv->progress_widget), "0 %");
	gtk_box_pack_start (GTK_BOX(vbox), priv->progress_widget, FALSE, FALSE, 0);

	priv->text_widget = gtk_label_new("");
	gtk_misc_set_alignment (GTK_MISC(priv->text_widget), 0.00F, 0.00F);
	gtk_label_set_line_wrap (GTK_LABEL(priv->text_widget), TRUE);

	gtk_box_pack_start (GTK_BOX(vbox), priv->text_widget, TRUE, TRUE, 0);

	GtkBox* pDialogVBox;
#if GTK_API_VERSION == 3
	pDialogVBox = GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG (dialog)));
#else
	pDialogVBox = GTK_BOX(GTK_DIALOG (dialog)->vbox);
#endif

	gtk_box_pack_start (pDialogVBox, vbox, FALSE, FALSE, 0);
	gtk_widget_show_all(vbox);


	gtk_dialog_add_buttons (GTK_DIALOG(dialog),
	    "gtk-close", GTK_RESPONSE_CLOSE, NULL);

	g_signal_connect(G_OBJECT(dialog), "response",
	    G_CALLBACK(on_dialog_response), NULL);

	gtk_window_set_deletable (GTK_WINDOW(dialog), FALSE);

	gtk_progress_dialog_set_button_close_enabled(dialog, FALSE);

	while (gtk_events_pending()) {
	    gtk_main_iteration();
	}

	return dialog;
}
