color_cancel
	(
	GtkWidget *dlg,
	gpointer data
	)
	{
	Palette_edit *paled = (Palette_edit *) data;
	if (paled->colorsel)
		gtk_widget_destroy(GTK_WIDGET(paled->colorsel));
	paled->colorsel = 0;
	}
