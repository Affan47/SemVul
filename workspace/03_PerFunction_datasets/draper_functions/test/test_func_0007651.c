on_button28_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *entry14, *entry15;

	char buf[64];

	printf("*** %s(): \n",__PRETTY_FUNCTION__);


	if(gpsdata && gpsdata->fix.latitude !=0)
	{
		entry14 = lookup_widget(GTK_WIDGET(button), "entry14");
		entry15 = lookup_widget(GTK_WIDGET(button), "entry15");

		g_sprintf(buf, "%f", gpsdata->fix.latitude);
		gtk_entry_set_text(GTK_ENTRY(entry14), buf);
		g_sprintf(buf, "%f", gpsdata->fix.longitude);
		gtk_entry_set_text(GTK_ENTRY(entry15), buf);
	}

}
