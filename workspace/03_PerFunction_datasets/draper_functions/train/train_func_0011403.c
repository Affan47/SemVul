gcide_idx_enumerate(struct gcide_idx_file *file,
		    int (*fun)(struct gcide_ref *, void *),
		    void *data)
{
    size_t i;

    for (i = 0; i < file->header.ihdr_num_pages; i++) {
	int j;

	struct gcide_idx_page *page = _idx_get_page(file, i);
	if (!page)
	    return -1;
	for (j = 0; j < page->ipg_header.hdr.phdr_numentries; j++)
	    if (fun(&page->ipg_ref[j], data))
		break;
    }
    return 0;
}
