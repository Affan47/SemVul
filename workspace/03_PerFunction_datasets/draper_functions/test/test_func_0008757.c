Hunk_Begin (int maxsize)
{

	Com_DPrintf("Hunk_Begin:0x%X:\n", maxsize );
	if ( hunk_base != NULL )
		Com_DPrintf("Warning: Hunk_Begin: hunk_base != NULL\n");


	rsvd_hunk_size = (size_t)maxsize + hunk_header_size;
	hunk_base = mmap(0, rsvd_hunk_size, PROT_READ|PROT_WRITE,
		MAP_PRIVATE|MAP_ANON, -1, 0);
	if ( hunk_base == NULL || hunk_base == (byte *)-1)
		Sys_Error("unable to virtual allocate %d bytes", maxsize);

	total_hunk_used_size = hunk_header_size;
	user_hunk_size = 0;
	user_hunk_base = hunk_base + hunk_header_size;


	phunk_size_store = (size_t *)hunk_base;
	*phunk_size_store = rsvd_hunk_size;

	return user_hunk_base;
}
