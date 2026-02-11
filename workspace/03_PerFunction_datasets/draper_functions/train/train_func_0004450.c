mg_create_center(window_t *sess, gtk_window_ui_t *gui, GtkWidget *box)
{
	GtkWidget *vbox, *hbox, *book;


	gui->vpane_left = gtk_vpaned_new();


	gui->vpane_right = gtk_vpaned_new();


	gui->hpane_left = gtk_hpaned_new();
	gtk_paned_set_position(GTK_PANED(gui->hpane_left), gui_pane_left_size_config);


	gui->hpane_right = gtk_hpaned_new();

	if (gui_tweaks_config & 4) {
		gtk_paned_pack2(GTK_PANED(gui->hpane_left), gui->vpane_left, FALSE, TRUE);
		gtk_paned_pack1(GTK_PANED(gui->hpane_left), gui->hpane_right, TRUE, TRUE);
	} else {
		gtk_paned_pack1(GTK_PANED(gui->hpane_left), gui->vpane_left, FALSE, TRUE);
		gtk_paned_pack2(GTK_PANED(gui->hpane_left), gui->hpane_right, TRUE, TRUE);
	}
	gtk_paned_pack2(GTK_PANED(gui->hpane_right), gui->vpane_right, FALSE, TRUE);

	gtk_container_add(GTK_CONTAINER(box), gui->hpane_left);

	gui->note_book = book = gtk_notebook_new();
	gtk_notebook_set_show_tabs(GTK_NOTEBOOK(book), FALSE);
	gtk_notebook_set_show_border(GTK_NOTEBOOK(book), FALSE);
	gtk_paned_pack1(GTK_PANED(gui->hpane_right), book, TRUE, TRUE);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_paned_pack1(GTK_PANED(gui->vpane_right), hbox, FALSE, TRUE);
	mg_create_userlist(gui, hbox);

	gui->user_box = hbox;

	vbox = gtk_vbox_new(FALSE, 3);
	gtk_notebook_append_page(GTK_NOTEBOOK(book), vbox, NULL);

	mg_create_topicbar(sess, vbox);
	mg_create_textarea(sess, vbox);
	mg_create_entry(sess, vbox);

	g_idle_add((GSourceFunc) mg_add_pane_signals, gui);
}
