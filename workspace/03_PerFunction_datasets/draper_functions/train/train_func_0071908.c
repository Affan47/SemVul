get_icon_name_from_selection (GladeNamedIconChooserDialog *dialog)
{
	GtkTreeIter  iter;
	GtkTreeModel *model;
	gchar        *name;

	if (!gtk_tree_selection_get_selected (dialog->priv->selection, &model, &iter))
		return NULL;

	gtk_tree_model_get (model, &iter,
			    ICONS_NAME_COLUMN, &name,
			    -1);

	return name;
}
