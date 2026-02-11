add_metadata(GwyContainer *container,
             NanoScanFile *nfile,
             gint id)
{
    GwyContainer *metadata;
    gchar *key;
    guint i;

    if (!nfile->meta->len)
        return;

    metadata = gwy_container_new();
    for (i = 0; i < nfile->meta->len; i++) {
        NanoScanMeta *meta = &g_array_index(nfile->meta, NanoScanMeta, i);

        if (meta->value)
            gwy_container_set_string_by_name(metadata, meta->name,
                                             g_strdup(meta->value));
    }

    key = g_strdup_printf("/%d/meta", id);
    gwy_container_set_object_by_name(container, key, metadata);
    g_free(key);
    g_object_unref(metadata);
}
