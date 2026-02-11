header_pax_extensions(struct archive_read *a, struct tar *tar,
    struct archive_entry *entry, const void *h, size_t *unconsumed)
{
	int err, err2;

	err = read_body_to_string(a, tar, &(tar->pax_header), h, unconsumed);
	if (err != ARCHIVE_OK)
		return (err);


	err = tar_read_header(a, tar, entry, unconsumed);
	if ((err != ARCHIVE_OK) && (err != ARCHIVE_WARN))
		return (err);


	err2 = pax_header(a, tar, entry, tar->pax_header.s);
	err =  err_combine(err, err2);
	tar->entry_padding = 0x1ff & (-tar->entry_bytes_remaining);
	return (err);
}
