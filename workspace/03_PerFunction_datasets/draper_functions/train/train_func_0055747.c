fm_path_entry_match_func(GtkEntryCompletion   *completion,
                                         const gchar          *key,
                                         GtkTreeIter          *iter,
                                         gpointer user_data)
{
    gboolean ret;
    GtkTreeModel *model = gtk_entry_completion_get_model(completion);
    FmPathEntry *entry = FM_PATH_ENTRY( gtk_entry_completion_get_entry(completion) );
    FmPathEntryPrivate *priv = FM_PATH_ENTRY_GET_PRIVATE(entry);
    char *model_basename;
    const char* typed_basename;

    typed_basename = gtk_entry_get_text(GTK_ENTRY(entry)) + priv->parent_len;
    gtk_tree_model_get(model, iter, COL_BASENAME, &model_basename, -1);

    if (G_UNLIKELY(model_basename == NULL))
        ret = FALSE;
    else if(model_basename[0] == '.' && typed_basename[0] != '.')
        ret = FALSE;
    else if(priv->long_list &&
            (typed_basename[0] == '\0'
             || (typed_basename[0] == '.' && typed_basename[1] == '\0')))
        ret = FALSE;
    else
        ret = g_str_has_prefix(model_basename, typed_basename);
    g_free(model_basename);
    return ret;
}
