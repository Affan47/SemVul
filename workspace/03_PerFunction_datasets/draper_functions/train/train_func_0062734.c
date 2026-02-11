create_pref_page(Plugin *p, GtkWidget *dialog)
{
	GtkWidget *page = NULL;

	if (p->configure)
	{
		page = p->configure(GTK_DIALOG(dialog));

		if (! GTK_IS_WIDGET(page))
		{
			geany_debug("Invalid widget returned from plugin_configure() in plugin \"%s\"!",
				p->info.name);
			return NULL;
		}
		else
		{
			GtkWidget *align = gtk_alignment_new(0.5, 0.5, 1, 1);

			gtk_alignment_set_padding(GTK_ALIGNMENT(align), 6, 6, 6, 6);
			gtk_container_add(GTK_CONTAINER(align), page);
			page = gtk_vbox_new(FALSE, 0);
			gtk_box_pack_start(GTK_BOX(page), align, TRUE, TRUE, 0);
		}
	}
	else if (p->configure_single)
	{
		GtkWidget *align = gtk_alignment_new(0.5, 0.5, 0, 0);
		GtkWidget *btn;

		gtk_alignment_set_padding(GTK_ALIGNMENT(align), 6, 6, 6, 6);

		btn = gtk_button_new_from_stock(GTK_STOCK_PREFERENCES);
		g_signal_connect(btn, "clicked", G_CALLBACK(on_pref_btn_clicked), p);
		gtk_container_add(GTK_CONTAINER(align), btn);
		page = align;
	}
	return page;
}
