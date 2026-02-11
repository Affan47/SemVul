e_send_options_dialog_run (ESendOptionsDialog *sod,
                           GtkWidget *parent,
                           Item_type type)
{
	ESendOptionsDialogPrivate *priv;
	GtkWidget *toplevel;

	g_return_val_if_fail (sod != NULL || E_IS_SEND_OPTIONS_DIALOG (sod), FALSE);

	priv = sod->priv;


	g_type_ensure (E_TYPE_DATE_EDIT);

	priv->builder = gtk_builder_new ();
	e_load_ui_builder_definition (priv->builder, "e-send-options.ui");

	if (!get_widgets (sod)) {
		g_object_unref (priv->builder);
		g_message (G_STRLOC ": Could not get the Widgets \n");
		return FALSE;
	}

	if (priv->global) {
		g_free (sod->data->sopts);
		sod->data->sopts = sod->data->mopts;
	}

	setup_widgets (sod, type);

	toplevel =  gtk_widget_get_toplevel (priv->main);
	if (parent)
		gtk_window_set_transient_for (GTK_WINDOW (toplevel),
				      GTK_WINDOW (parent));

	e_send_options_fill_widgets_with_data (sod);
	sensitize_widgets (sod);
	init_widgets (sod);
	gtk_window_set_modal ((GtkWindow *) priv->main, TRUE);

	gtk_widget_show (priv->main);

	return TRUE;
}
