build_top(MainInfo *min)
{
	GtkLabel	**label = (GtkLabel **) &min->gui->top;
	GtkWidget	*top, *lab;

	if(min->cfg.errors.display == ERR_DISPLAY_TITLEBAR)
	{
		if(*label != NULL)
			gtk_widget_destroy(GTK_WIDGET(*label));
		*label = NULL;
		return NULL;
	}

	top = gtk_event_box_new();
	lab = gtk_label_new("");
	gtk_container_add(GTK_CONTAINER(top), lab);
	gtk_widget_show_all(top);
	if(label != NULL)
		*label = GTK_LABEL(lab);
	g_signal_connect(G_OBJECT(top), "button_press_event", G_CALLBACK(evt_top_button_press_event), min);

	return top;
}
