ecs_detect(const GwyFileDetectInfo *fileinfo,
           gboolean only_name)
{
    guint xres, yres;
    const guchar *p;

    if (only_name)
        return g_str_has_suffix(fileinfo->name_lowercase, EXTENSION) ? 10 : 0;

    if (fileinfo->buffer_len < ECS_RESOLUTION + 2*2
        || fileinfo->file_size < HEADER_SIZE + 2
        || memcmp(fileinfo->head, MAGIC, MAGIC_SIZE) != 0)
        return 0;


    p = fileinfo->head + ECS_RESOLUTION;
    xres = gwy_get_guint16_le(&p);
    yres = gwy_get_guint16_le(&p);

    if (fileinfo->file_size != 2*xres*yres + HEADER_SIZE)
        return 0;

    return 100;
}
