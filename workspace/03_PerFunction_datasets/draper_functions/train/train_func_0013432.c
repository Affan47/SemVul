archive_entry_clear(struct archive_entry *entry)
{
    if (entry == NULL)
        return (NULL);
    aes_clean(&entry->ae_fflags_text);
    aes_clean(&entry->ae_gname);
    aes_clean(&entry->ae_hardlink);
    aes_clean(&entry->ae_pathname);
    aes_clean(&entry->ae_sourcepath);
    aes_clean(&entry->ae_symlink);
    aes_clean(&entry->ae_uname);
    archive_entry_acl_clear(entry);
    archive_entry_xattr_clear(entry);
    free(entry->stat);
    memset(entry, 0, sizeof(*entry));
    return entry;
}
