_select_by_data_func(GtkTreeModel *model, GtkTreePath *path,
		GtkTreeIter *iter, ComboboxSelCtx *ctx)
{
	GtkComboBox *combobox = ctx->combobox;
	gchar *data = ctx->data;
	gchar *curdata;

	gtk_tree_model_get(GTK_TREE_MODEL(model), iter, COMBOBOX_DATA, &curdata, -1);
	if ( data != NULL && curdata != NULL && !strcmp(data, curdata) ) {
		gtk_combo_box_set_active_iter(combobox, iter);
		return TRUE;
	}

	return FALSE;
}
