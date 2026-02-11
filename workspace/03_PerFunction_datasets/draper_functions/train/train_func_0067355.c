gtkutil_button (GtkWidget *box, char *stock, char *tip, void *callback,
					 void *userdata, char *labeltext)
{
	GtkWidget *wid, *img, *bbox;

	wid = gtk_button_new ();

	if (labeltext)
	{
		gtk_button_set_label (GTK_BUTTON (wid), labeltext);
		gtk_button_set_image (GTK_BUTTON (wid), gtk_image_new_from_stock (stock, GTK_ICON_SIZE_MENU));
		gtk_button_set_use_underline (GTK_BUTTON (wid), TRUE);
		if (box)
			gtk_container_add (GTK_CONTAINER (box), wid);
	}
	else
	{
		bbox = gtk_hbox_new (0, 0);
		gtk_container_add (GTK_CONTAINER (wid), bbox);
		gtk_widget_show (bbox);

		img = gtk_image_new_from_stock (stock, GTK_ICON_SIZE_MENU);
		if (strcmp (stock, GTK_STOCK_GOTO_LAST) == 0)
		{
			gtk_widget_set_usize (img, 10, 6);
		}
		gtk_container_add (GTK_CONTAINER (bbox), img);
		gtk_widget_show (img);
		gtk_box_pack_start (GTK_BOX (box), wid, 0, 0, 0);
	}

	g_signal_connect (G_OBJECT (wid), "clicked",
							G_CALLBACK (callback), userdata);
	gtk_widget_show (wid);
	if (tip)
		add_tip (wid, tip);

	return wid;
}
