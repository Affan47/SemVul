archive_entry_fflags_text(struct archive_entry *entry)
{
    const char *f;
    char *p;

    f = aes_get_mbs(&entry->ae_fflags_text);
    if (f != NULL)
        return (f);

    if (entry->ae_fflags_set == 0  &&  entry->ae_fflags_clear == 0)
        return (NULL);

    p = ae_fflagstostr(entry->ae_fflags_set, entry->ae_fflags_clear);
    if (p == NULL)
        return (NULL);

    aes_copy_mbs(&entry->ae_fflags_text, p);
    free(p);
    f = aes_get_mbs(&entry->ae_fflags_text);
    return (f);
}
