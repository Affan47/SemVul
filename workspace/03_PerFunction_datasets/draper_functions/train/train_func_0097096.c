jeol_detect(const GwyFileDetectInfo *fileinfo, gboolean only_name)
{
    if (only_name)
        return 0;

    if (fileinfo->buffer_len <= MAGIC_SIZE
        || memcmp(fileinfo->head, MAGIC, MAGIC_SIZE) != 0
        || fileinfo->file_size < JEOL_DATA_START)
        return 0;


    return 90;
}
