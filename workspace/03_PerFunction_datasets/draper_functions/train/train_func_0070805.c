createc_detect(const GwyFileDetectInfo *fileinfo,
               gboolean only_name)
{
    if (only_name)
        return g_str_has_suffix(fileinfo->name_lowercase, ".dat") ? 10 : 0;

    if (createc_get_version(fileinfo->head, fileinfo->buffer_len))
        return 100;

    return 0;
}
