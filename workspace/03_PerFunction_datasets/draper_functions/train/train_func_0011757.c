fm_path_entry_set_path(FmPathEntry *entry, FmPath* path)
{
    FmPathEntryPrivate *priv = FM_PATH_ENTRY_GET_PRIVATE(entry);

    if(priv->path)
        fm_path_unref(priv->path);

    if(path)
    {
        priv->path = fm_path_ref(path);
        _set_entry_text_from_path(GTK_ENTRY(entry), priv);
    }
    else
    {
        priv->path = NULL;
        gtk_entry_set_text(GTK_ENTRY(entry), "");
    }
}
