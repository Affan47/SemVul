fn_hash_intl(fs_query *q, fs_value arg, GChecksumType type)
{
    if (!fs_is_plain_or_string(arg)) {
        return fs_value_error(FS_ERROR_INVALID_TYPE, NULL);
    }
    arg = fs_value_fill_lexical(q, arg);

    GChecksum *sum = g_checksum_new(type);
    g_checksum_update(sum, (guchar *)arg.lex, -1);
    char *str = g_strdup(g_checksum_get_string(sum));
    g_checksum_free(sum);
    fs_query_add_freeable(q, str);

    return fs_value_plain(str);
}
