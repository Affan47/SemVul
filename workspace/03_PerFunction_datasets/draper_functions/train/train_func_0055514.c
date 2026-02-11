e_categories_editor_set_entry_visible (ECategoriesEditor *editor,
                                       gboolean entry_visible)
{
	g_return_if_fail (E_IS_CATEGORIES_EDITOR (editor));

	if ((gtk_widget_get_visible (editor->priv->categories_entry) ? 1 : 0) ==
	    (entry_visible ? 1 : 0))
		return;

	gtk_widget_set_visible (
		editor->priv->categories_entry, entry_visible);
	gtk_widget_set_visible (
		editor->priv->categories_entry_label, entry_visible);
	e_categories_selector_set_items_checkable (
		editor->priv->categories_list, entry_visible);

	g_object_notify (G_OBJECT (editor), "entry-visible");
}
