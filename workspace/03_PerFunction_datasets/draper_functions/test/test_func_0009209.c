value_toggled (GtkCellRendererToggle *cell_renderer,
	       gchar                 *path,
	       GladeEPropAttrs       *eprop_attrs)
{
	gboolean         active;
	GtkTreeIter      iter;
	PangoAttrType    type;

	if (!gtk_tree_model_get_iter_from_string (eprop_attrs->model, &iter, path))
		return;

	gtk_tree_model_get (eprop_attrs->model, &iter,
			    COLUMN_TOGGLE_DOWN, &active,
			    COLUMN_TYPE, &type,
			    -1);

	gtk_list_store_set (GTK_LIST_STORE (eprop_attrs->model), &iter,
			    COLUMN_NAME_WEIGHT, PANGO_WEIGHT_BOLD,
			    COLUMN_TOGGLE_DOWN, !active,
			    -1);

	sync_object (eprop_attrs, FALSE);
}
