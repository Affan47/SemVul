tsc_parse_text_fields(GHashTable *globalhash, const gchar *prefix,
                      TescanBlock *block)
{
    BlockCopyInfo block_copy_info;
    GwyTextHeaderParser parser;
    GHashTable *hash;
    gchar *data;

    data = g_new(gchar, block->size-1);
    memcpy(data, block->data, block->size-2);
    data[block->size-2] = '\0';

    gwy_clear(&parser, 1);
    parser.key_value_separator = "=";
    hash = gwy_text_header_parse(data, &parser, NULL, NULL);

    block_copy_info.target = globalhash;
    block_copy_info.prefix = prefix;
    g_hash_table_foreach(hash, copy_with_prefix, &block_copy_info);

    g_free(data);
    g_hash_table_destroy(hash);
}
