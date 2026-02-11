generic_dialog_show_cb(GtkWidget *widget, gpointer data)
{
	GenericDialog *gd = data;
	if (gd->cancel_button)
		{
		gtk_box_reorder_child(GTK_BOX(gd->hbox), gd->cancel_button, -1);
		}

	g_signal_handlers_disconnect_by_func(G_OBJECT(widget),
					     G_CALLBACK(generic_dialog_show_cb), gd);
}
