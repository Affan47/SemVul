pgd_transitions_create_widget (PopplerDocument *document)
{
	PgdTransitionsDemo *demo;
	GtkWidget          *vbox;
	GtkListStore       *model;
	GtkWidget          *swindow;
	GtkWidget          *hbox, *button;

	demo = g_new0 (PgdTransitionsDemo, 1);

	demo->doc = g_object_ref (document);

	vbox = gtk_vbox_new (FALSE, 12);

	hbox = gtk_hbox_new (FALSE, 6);

	demo->progress = gtk_progress_bar_new ();
	gtk_progress_bar_set_ellipsize (GTK_PROGRESS_BAR (demo->progress),
					PANGO_ELLIPSIZE_END);
	gtk_box_pack_start (GTK_BOX (hbox), demo->progress, TRUE, TRUE, 0);
	gtk_widget_show (demo->progress);

	button = gtk_button_new_with_label ("Scan");
	g_signal_connect (G_OBJECT (button), "clicked",
			  G_CALLBACK (pgd_transitions_scan_button_clicked),
			  (gpointer)demo);
	gtk_box_pack_end (GTK_BOX (hbox), button, FALSE, FALSE, 0);
	gtk_widget_show (button);

	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, TRUE, 6);
	gtk_widget_show (hbox);

	swindow = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (swindow),
					GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	model = gtk_list_store_new (N_COLUMNS,
				    G_TYPE_STRING, G_TYPE_STRING,
				    G_TYPE_STRING, G_TYPE_STRING,
				    G_TYPE_STRING, G_TYPE_STRING,
				    G_TYPE_STRING, G_TYPE_STRING);
	demo->treeview = pgd_transitions_create_list (GTK_TREE_MODEL (model));
	g_object_unref (model);

	gtk_container_add (GTK_CONTAINER (swindow), demo->treeview);
	gtk_widget_show (demo->treeview);

	gtk_box_pack_start (GTK_BOX (vbox), swindow, TRUE, TRUE, 0);
	gtk_widget_show (swindow);

	g_object_weak_ref (G_OBJECT (swindow),
			   (GWeakNotify)pgd_transitions_free,
			   (gpointer)demo);

	return vbox;
}
