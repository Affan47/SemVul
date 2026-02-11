go_up_button_clicked_cb (GtkButton *button,
			 gpointer   user_data)
{
	FrFileSelectorDialog *self = user_data;
	GFile                *parent;

	if (self->priv->current_folder == NULL)
		return;

	parent = g_file_get_parent (self->priv->current_folder);
	if (parent == NULL)
		return;

	fr_file_selector_dialog_set_current_folder (self, parent);

	g_object_unref (parent);
}
