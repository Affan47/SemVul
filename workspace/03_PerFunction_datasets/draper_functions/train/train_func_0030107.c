collect_locales_from_archive (void)
{
        GMappedFile        *mapped;
        GError             *error;
        char               *addr;
        struct locarhead   *head;
        struct namehashent *namehashtab;
        struct nameent     *names;
        uint32_t            used;
        uint32_t            cnt;
        gsize               len;
        gboolean            locales_collected;

        error = NULL;
        mapped = g_mapped_file_new (ARCHIVE_FILE, FALSE, &error);
        if (mapped == NULL) {
                mapped = g_mapped_file_new (SYSTEM_ARCHIVE_FILE, FALSE, NULL);
                if (mapped == NULL) {
                        g_warning ("Mapping failed for %s: %s", ARCHIVE_FILE, error->message);
                        g_error_free (error);
                        return FALSE;
                }
                g_error_free (error);
        }

        locales_collected = FALSE;

        addr = g_mapped_file_get_contents (mapped);
        len = g_mapped_file_get_length (mapped);

        head = (struct locarhead *) addr;
        if (head->namehash_offset + head->namehash_size > len
            || head->string_offset + head->string_size > len
            || head->locrectab_offset + head->locrectab_size > len
            || head->sumhash_offset + head->sumhash_size > len) {
                goto out;
        }

        namehashtab = (struct namehashent *) (addr + head->namehash_offset);

        names = (struct nameent *) g_new0 (struct nameent, head->namehash_used);
        for (cnt = used = 0; cnt < head->namehash_size; ++cnt) {
                if (namehashtab[cnt].locrec_offset != 0) {
                        names[used].name = addr + namehashtab[cnt].name_offset;
                        names[used++].locrec_offset = namehashtab[cnt].locrec_offset;
                }
        }

        for (cnt = 0; cnt < used; ++cnt) {
                add_locale (names[cnt].name, TRUE);
        }

        g_free (names);

        locales_collected = TRUE;
 out:

        g_mapped_file_unref (mapped);
        return locales_collected;
}
