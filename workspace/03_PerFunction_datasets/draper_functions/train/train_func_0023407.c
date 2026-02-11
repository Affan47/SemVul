_path_entry_is_single_match(FmPathEntry *entry, FmPathEntryPrivate *priv)
{
    GtkTreeModel *model = GTK_TREE_MODEL(priv->model);
    char *model_basename;
    const char* typed_basename;
    GtkTreeIter it;
    gboolean partial = FALSE, match = FALSE;

    typed_basename = gtk_entry_get_text(GTK_ENTRY(entry)) + priv->parent_len;
    if (gtk_tree_model_get_iter_first(model, &it)) do
    {
        gtk_tree_model_get(model, &it, COL_BASENAME, &model_basename, -1);
        if (!match && strcmp(model_basename, typed_basename) == 0)
            match = TRUE;
        else if (g_str_has_prefix(model_basename, typed_basename))
            partial = TRUE;
        g_free(model_basename);
    }
    while (!partial && gtk_tree_model_iter_next(model, &it));

    return (match && !partial);
}
