jbig2_metadata_add(Jbig2Ctx *ctx, Jbig2Metadata *md,
                        const char *key, const int key_length,
                        const char *value, const int value_length)
{
    char **keys, **values;


    if (md->entries == md->max_entries) {
        md->max_entries <<= 1;
        keys = jbig2_renew(ctx, md->keys, char*, md->max_entries);
        values = jbig2_renew(ctx, md->values, char*, md->max_entries);
        if (keys == NULL || values == NULL) {
            jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1,
                "unable to resize metadata structure");
            return -1;
        }
        md->keys = keys;
        md->values = values;
    }


    md->keys[md->entries] = jbig2_strndup(ctx, key, key_length);
    md->values[md->entries] = jbig2_strndup(ctx, value, value_length);
    md->entries++;

    return 0;
}
