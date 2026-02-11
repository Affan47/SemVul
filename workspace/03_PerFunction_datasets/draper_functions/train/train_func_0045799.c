toplevel_create(seaudit_t * s)
{
	toplevel_t *top;
	GtkWidget *vbox;
	int error = 0;

	if ((top = calloc(1, sizeof(*top))) == NULL || (top->views = apol_vector_create(message_view_free)) == NULL) {
		error = errno;
		goto cleanup;
	}
	top->s = s;
	top->next_model_number = 1;

	if ((top->xml_filename = apol_file_find_path("seaudit.glade")) == NULL ||
	    (top->xml = glade_xml_new(top->xml_filename, "TopLevel", NULL)) == NULL) {
		fprintf(stderr, "Could not open seaudit.glade.\n");
		error = EIO;
		goto cleanup;
	}
	top->w = GTK_WINDOW(glade_xml_get_widget(top->xml, "TopLevel"));
	g_object_set_data(G_OBJECT(top->w), "toplevel", top);
	init_icons(top);
	top->notebook = GTK_NOTEBOOK(gtk_notebook_new());
	g_signal_connect_after(G_OBJECT(top->notebook), "switch-page", G_CALLBACK(toplevel_on_notebook_switch_page), top);
	vbox = glade_xml_get_widget(top->xml, "NotebookVBox");
	gtk_container_add(GTK_CONTAINER(vbox), GTK_WIDGET(top->notebook));
	gtk_widget_show(GTK_WIDGET(top->notebook));
	gtk_widget_show(GTK_WIDGET(top->w));
	toplevel_set_recent_logs_submenu(top);
	toplevel_set_recent_policies_submenu(top);

	glade_xml_signal_autoconnect(top->xml);


	toplevel_add_new_model(top);


	if ((top->pv = policy_view_create(top)) == NULL || (top->progress = progress_create(top)) == NULL) {
		error = errno;
		goto cleanup;
	}
      cleanup:
	if (error != 0) {
		toplevel_destroy(&top);
		errno = error;
		return NULL;
	}
	return top;
}
