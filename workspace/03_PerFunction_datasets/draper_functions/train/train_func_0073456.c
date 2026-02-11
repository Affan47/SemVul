addressbook_edit_person_widgets_create( GtkWidget* container, gboolean *cancelled )
{
	GtkWidget *vbox;
	GtkWidget *vnbox;
	GtkWidget *notebook;
	GtkWidget *hbbox;
	GtkWidget *ok_btn;
	GtkWidget *cancel_btn;

	vbox = gtk_vbox_new(FALSE, 4);
	 gtk_container_set_border_width(GTK_CONTAINER(vbox), BORDER_WIDTH);
	gtk_widget_show(vbox);
	gtk_container_add(GTK_CONTAINER(container), vbox);

	vnbox = gtk_vbox_new(FALSE, 4);
	gtk_container_set_border_width(GTK_CONTAINER(vnbox), 4);
	gtk_widget_show(vnbox);
	gtk_box_pack_start(GTK_BOX(vbox), vnbox, TRUE, TRUE, 0);


	notebook = gtk_notebook_new();
	gtk_widget_show(notebook);
	gtk_box_pack_start(GTK_BOX(vnbox), notebook, TRUE, TRUE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(notebook), 6);


	if (prefs_common.addressbook_use_editaddress_dialog)
	gtkut_stock_button_set_create(&hbbox, &cancel_btn, GTK_STOCK_CANCEL,
				      &ok_btn, GTK_STOCK_OK,
				      NULL, NULL);
	else
		gtkut_stock_with_text_button_set_create(&hbbox,
					  &cancel_btn, GTK_STOCK_CANCEL, _("Discard"),
				      &ok_btn, GTK_STOCK_OK, _("Apply"),
				      NULL, NULL, NULL);
	gtk_box_pack_end(GTK_BOX(vnbox), hbbox, FALSE, FALSE, 0);
	gtk_widget_grab_default(ok_btn);

	g_signal_connect(G_OBJECT(ok_btn), "clicked",
			 G_CALLBACK(edit_person_ok), cancelled);
	g_signal_connect(G_OBJECT(cancel_btn), "clicked",
			 G_CALLBACK(edit_person_cancel), cancelled);
	g_signal_connect(G_OBJECT(notebook), "switch_page",
			 G_CALLBACK(edit_person_switch_page), NULL );

	gtk_widget_show_all(vbox);

	personeditdlg.notebook   = notebook;
	personeditdlg.ok_btn     = ok_btn;
	personeditdlg.cancel_btn = cancel_btn;

	return vbox;
}
