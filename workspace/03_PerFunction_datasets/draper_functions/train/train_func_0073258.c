write_template_header(struct libjte_env *o)
{
    char buf[2048];
    int i = 0;
    char *p = buf;

#ifndef LIBJTE_WITH_LIBBZ2

    if (o->jte_template_compression == JTE_TEMP_BZIP2) {
        sprintf(o->message_buffer,
            "libjte: Compression algorithm BZIP2 not enabled at compile time");
        libjte_add_msg_entry(o, o->message_buffer, 0);
        exit_if_enabled(o, 1);
        return -1;
    }

#endif

    memset(buf, 0, sizeof(buf));

    if (o->template_context != NULL)
        checksum_free_context(o->template_context);
    o->template_context = checksum_init_context(o->checksum_algo_tmpl,
                                                "template");
    if (o->template_context == NULL)
    {
        sprintf(o->message_buffer,
                "cannot allocate template checksum contexts");
        libjte_add_msg_entry(o, o->message_buffer, 0);
        exit_if_enabled(o, 1);
        return -1;
    }

    i += sprintf(p, "JigsawDownload template %s libjte-%d.%d.%d \r\n",
             JIGDO_TEMPLATE_VERSION,
             LIBJTE_VERSION_MAJOR, LIBJTE_VERSION_MINOR, LIBJTE_VERSION_MICRO);
    p = &buf[i];

    i += sprintf(p, "%s \r\n", JTE_COMMENT);
    p = &buf[i];

    i += sprintf(p, "\r\n");
    if (template_fwrite(o, buf, i, 1, o->t_file) <= 0)
        return 0;
    return 1;
}
