gnu_sparse_old_parse(struct archive_read *a, struct tar *tar,
    const struct gnu_sparse *sparse, int length)
{
	while (length > 0 && sparse->offset[0] != 0) {
		if (gnu_add_sparse_entry(a, tar,
		    tar_atol(sparse->offset, sizeof(sparse->offset)),
		    tar_atol(sparse->numbytes, sizeof(sparse->numbytes)))
		    != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		sparse++;
		length--;
	}
	return (ARCHIVE_OK);
}
