omicron_detect(const GwyFileDetectInfo *fileinfo,
               gboolean only_name)
{
    const gchar *p = fileinfo->head;

    if (only_name)
        return g_str_has_suffix(fileinfo->name_lowercase, EXTENSION_HEADER)
               ? 15 : 0;


    if (fileinfo->buffer_len < 100)
        return 0;

    p = fileinfo->head;
    if (*p != ';' || !(p = strchr(p+1, ';')) || !(p = strchr(p+1, ';')))
        return 0;

    do {
        p++;
    } while (g_ascii_isspace(*p));
    if (memcmp(p, MAGIC, MAGIC_SIZE) == 0)
        return 100;

    return 0;
}
