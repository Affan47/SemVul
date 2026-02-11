subst_insert_unique (gchar *byte_sequence, conv_type *conv,
                     GncXmlImportData *data)
{
    if (!data->subst)
        return;
    g_hash_table_insert (data->subst, g_strdup (byte_sequence),
                         g_strdup (conv->utf8_string));
}
