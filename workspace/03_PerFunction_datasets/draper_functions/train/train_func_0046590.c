indigui_create_number_widget(struct indi_prop_t *iprop, int num_props)
{
	int pos = 0;
	GtkWidget *value;
	GtkWidget *entry;
	GtkWidget *button;
	indi_list *isl;
	char val[80];
	unsigned long signal;

	for (isl = il_iter(iprop->elems); ! il_is_last(isl); isl = il_next(isl), pos++) {
		struct indi_elem_t *elem = (struct indi_elem_t *)il_item(isl);

		gtk_table_attach(GTK_TABLE (iprop->widget),
			gtk_label_new(elem->label),
			0, 1, pos, pos + 1,
			(GtkAttachOptions)(GTK_FILL | GTK_EXPAND), GTK_FILL, 0, 0);

		sprintf(val, "%f", elem->value.num.value);
		value = gtk_label_new(val);
		g_object_ref(G_OBJECT (value));
		g_object_set_data(G_OBJECT (iprop->widget), elem->name, value);
		gtk_table_attach(GTK_TABLE (iprop->widget),
			value,
			1, 2, pos, pos + 1,
			(GtkAttachOptions)(GTK_FILL | GTK_EXPAND), GTK_FILL, 0, 0);

		if (iprop->permission != INDI_RO) {
			entry = gtk_entry_new();
			g_object_ref(G_OBJECT (entry));
			g_object_set_data(G_OBJECT (value), "entry", entry);
			gtk_table_attach(GTK_TABLE (iprop->widget),
				entry,
				2, 3, pos, pos + 1,
				(GtkAttachOptions)(GTK_FILL | GTK_EXPAND), GTK_FILL, 0, 0);
		}
	}
	if (iprop->permission != INDI_RO) {
		button = gtk_button_new_with_label("Set");
		signal = g_signal_connect(G_OBJECT (button), "clicked", G_CALLBACK (indigui_send_cb), iprop);
		indigui_prop_add_signal(iprop, button, signal);
		gtk_table_attach(GTK_TABLE (iprop->widget),
			button,
			3, 4, 0, num_props,
			(GtkAttachOptions)(GTK_FILL | GTK_EXPAND), GTK_FILL, 0, 0);
	}
}
