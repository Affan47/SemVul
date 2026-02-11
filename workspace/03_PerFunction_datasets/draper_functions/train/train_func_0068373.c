nfs_readdir_page_filler(nfs_readdir_descriptor_t *desc, struct nfs_entry *entry,
				struct page **xdr_pages, struct page *page, unsigned int buflen)
{
	struct xdr_stream stream;
	struct xdr_buf buf;
	struct page *scratch;
	struct nfs_cache_array *array;
	unsigned int count = 0;
	int status;

	scratch = alloc_page(GFP_KERNEL);
	if (scratch == NULL)
		return -ENOMEM;

	if (buflen == 0)
		goto out_nopages;

	xdr_init_decode_pages(&stream, &buf, xdr_pages, buflen);
	xdr_set_scratch_buffer(&stream, page_address(scratch), PAGE_SIZE);

	do {
		status = xdr_decode(desc, entry, &stream);
		if (status != 0) {
			if (status == -EAGAIN)
				status = 0;
			break;
		}

		count++;

		if (desc->plus != 0)
			nfs_prime_dcache(file_dentry(desc->file), entry);

		status = nfs_readdir_add_to_array(entry, page);
		if (status != 0)
			break;
	} while (!entry->eof);

out_nopages:
	if (count == 0 || (status == -EBADCOOKIE && entry->eof != 0)) {
		array = nfs_readdir_get_array(page);
		if (!IS_ERR(array)) {
			array->eof_index = array->size;
			status = 0;
			nfs_readdir_release_array(page);
		} else
			status = PTR_ERR(array);
	}

	put_page(scratch);
	return status;
}
