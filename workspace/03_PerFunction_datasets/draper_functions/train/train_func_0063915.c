pref_box_new(GtkWidget *parent_box, gboolean fill,
			GtkOrientation orientation, gboolean padding)
{
	GtkWidget *box;

	if (orientation == GTK_ORIENTATION_HORIZONTAL)
		{
		box = gtk_hbox_new(FALSE, padding);
		}
	else
		{
		box = gtk_vbox_new(FALSE, padding);
		}

	gtk_box_pack_start(GTK_BOX(parent_box), box, fill, fill, 0);
	gtk_widget_show(box);

	return box;
}
