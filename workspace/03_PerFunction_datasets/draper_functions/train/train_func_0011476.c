glade_signal_editor_userdata_editing_done (GladeSignalEditor *self,
                                           const gchar *signal_name,
                                           const gchar *old_userdata,
                                           const gchar *new_userdata,
                                           GtkTreeIter *iter)
{
	GladeSignalEditorPrivate *priv = self->priv;
	GtkTreeModel *model = GTK_TREE_MODEL (priv->model);
	GladeWidget  *glade_widget = priv->widget;
	gchar *handler;
	gboolean after, swapped;
	GladeSignal *old_signal, *new_signal;

	gtk_tree_model_get (model,               iter,
			    GSE_COLUMN_HANDLER,  &handler,
			    GSE_COLUMN_AFTER,    &after,
			    GSE_COLUMN_SWAPPED,  &swapped,
			    -1);


	if (new_userdata == NULL)
	{
		gtk_tree_store_set (GTK_TREE_STORE (model), iter,
				    GSE_COLUMN_USERDATA_SLOT,   TRUE,
				    GSE_COLUMN_USERDATA,        USERDATA_DEFAULT,
				    GSE_COLUMN_SWAPPED,         FALSE,
				    GSE_COLUMN_SWAPPED_VISIBLE, FALSE, -1);
	}
	else
	{
		gtk_tree_store_set (GTK_TREE_STORE (model), iter,
				    GSE_COLUMN_USERDATA_SLOT,   FALSE,
				    GSE_COLUMN_USERDATA,        new_userdata,
				    GSE_COLUMN_SWAPPED_VISIBLE, TRUE,
				    -1);
	}

	old_signal = glade_signal_new (signal_name, handler, old_userdata, after, swapped);

	new_signal = glade_signal_new (signal_name, handler, new_userdata, after, swapped);

	if (glade_signal_equal (old_signal, new_signal) == FALSE)
		glade_command_change_signal (glade_widget, old_signal, new_signal);

	glade_signal_free (old_signal);
	glade_signal_free (new_signal);

	g_free (handler);
	return FALSE;
}
