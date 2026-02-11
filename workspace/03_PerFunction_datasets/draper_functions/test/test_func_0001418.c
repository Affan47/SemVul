renderer_edited(GtkCellRendererText * cell,
			    const gchar * path_string,
			    const gchar * new_text, gpointer user_data)
{
	GtkTreeModel *model = GTK_TREE_MODEL(tree);
	GtkTreePath *path = gtk_tree_path_new_from_string(path_string);
	GtkTreeIter iter;
	const char *old_text;
	VarEntry *ve;
	gchar *str;
	VarEntry *arg;

	if (!gtk_tree_model_get_iter(model, &iter, path))
		return;

	gtk_tree_model_get(model, &iter, COLUMN_NAME, &old_text, -1);
	gtk_tree_model_get(model, &iter, COLUMN_DATA, &ve, -1);


	str = ticonv_varname_tokenize(GFMFile.model, new_text, ve->type);
	arg = tifiles_ve_dup(ve);
	if(strlen(str) > 8)
		str[8] = '\0';
	strcpy(arg->name, str);
	g_free(str);

	if(ticalcs_dirlist_ve_exist(GFMFile.trees.vars, arg))
	{
		msgbox_one(MSGBOX_INFO, _("The name already exists. Please choose another one..."));
		tifiles_ve_delete(arg);
		return;
	}


	strcpy(ve->name, arg->name);
	tifiles_ve_delete(arg);

	gtk_tree_store_set(tree, &iter, COLUMN_NAME, new_text, -1);
	gtk_tree_path_free(path);

	enable_save(TRUE);
}
