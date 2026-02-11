toplevel_on_edit_menu_activate(gpointer user_data, GtkMenuItem * widget __attribute__ ((unused)))
{
	toplevel_t *top = g_object_get_data(G_OBJECT(user_data), "toplevel");
	GtkTextView *view = toplevel_get_text_view(top);
	GtkTextBuffer *txt = gtk_text_view_get_buffer(view);
	GtkWidget *copy = glade_xml_get_widget(top->xml, "Copy");
	GtkWidget *select_all = glade_xml_get_widget(top->xml, "Select All");
	GtkTextIter start, end;
	assert(copy != NULL && select_all != NULL);


	if (gtk_text_buffer_get_selection_bounds(txt, &start, &end)) {
		gtk_widget_set_sensitive(copy, TRUE);
	} else {
		gtk_widget_set_sensitive(copy, FALSE);
	}


	gtk_text_buffer_get_start_iter(txt, &start);
	gtk_text_buffer_get_end_iter(txt, &end);
	if (gtk_text_iter_get_offset(&start) == gtk_text_iter_get_offset(&end)) {
		gtk_widget_set_sensitive(select_all, FALSE);
	} else {
		gtk_widget_set_sensitive(select_all, TRUE);
	}
}
