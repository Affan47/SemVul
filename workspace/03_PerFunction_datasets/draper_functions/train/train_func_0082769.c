header_longlink(struct archive_read *a, struct tar *tar,
    struct archive_entry *entry, const void *h)
{
    int err;

    err = read_body_to_string(a, tar, &(tar->longlink), h);
    if (err != ARCHIVE_OK)
        return (err);
    err = tar_read_header(a, tar, entry);
    if ((err != ARCHIVE_OK) && (err != ARCHIVE_WARN))
        return (err);

    archive_entry_copy_link(entry, tar->longlink.s);
    return (ARCHIVE_OK);
}
