gth_tags_entry_set_expanded (GthTagsEntry *self,
			     gboolean      expanded)
{
	g_return_if_fail (GTH_IS_TAGS_ENTRY (self));

	self->priv->expanded = expanded;
	gtk_widget_set_size_request (self->priv->expanded_list.container, -1, self->priv->expanded ? -1 : EXPANDED_LIST_HEIGHT);
	gtk_widget_set_visible (self->priv->expand_button, ! expanded);
	gtk_widget_set_visible (self->priv->expanded_list.container, expanded || gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (self->priv->expand_button)));
}
