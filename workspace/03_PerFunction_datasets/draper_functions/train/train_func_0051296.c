is_diskdump(char *file)
{
	int sz, i;

	if (!open_dump_file(file) || !read_dump_header(file))
		return FALSE;

	sz = dd->block_size * (DISKDUMP_CACHED_PAGES);
	if ((dd->page_cache_buf = malloc(sz)) == NULL)
		error(FATAL, "%s: cannot malloc compressed page_cache_buf\n",
			DISKDUMP_VALID() ? "diskdump" : "compressed kdump");

	for (i = 0; i < DISKDUMP_CACHED_PAGES; i++)
		dd->page_cache_hdr[i].pg_bufptr =
			&dd->page_cache_buf[i * dd->block_size];

	if ((dd->compressed_page = (char *)malloc(dd->block_size)) == NULL)
		error(FATAL, "%s: cannot malloc compressed page space\n",
			DISKDUMP_VALID() ? "diskdump" : "compressed kdump");

	if (CRASHDEBUG(1))
		__diskdump_memory_dump(fp);

	if (pc->flags2 & GET_OSRELEASE)
		diskdump_get_osrelease();

#ifdef LZO
	if (lzo_init() == LZO_E_OK)
		dd->flags |= LZO_SUPPORTED;
#endif

#ifdef SNAPPY
	dd->flags |= SNAPPY_SUPPORTED;
#endif

	if ((pc->flags2 & GET_LOG) && KDUMP_CMPRS_VALID()) {
		pc->dfd = dd->dfd;
		pc->readmem = read_diskdump;
		pc->flags |= DISKDUMP;
		get_log_from_vmcoreinfo(file, vmcoreinfo_read_string);
	}

	return TRUE;
}
