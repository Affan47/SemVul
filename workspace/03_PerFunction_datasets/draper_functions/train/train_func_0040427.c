alloc_sb (Descriptor *desc)
{
	static int pagesize = -1;

	gpointer sb_header;

	if (pagesize == -1)
		pagesize = mono_pagesize ();

	sb_header = desc->block_size == pagesize ?
		mono_valloc (NULL, desc->block_size, prot_flags_for_activate (TRUE)) :
		mono_valloc_aligned (desc->block_size, desc->block_size, prot_flags_for_activate (TRUE));

	g_assert (sb_header == sb_header_for_addr (sb_header, desc->block_size));

	*(Descriptor**)sb_header = desc;


	return (char*)sb_header + LOCK_FREE_ALLOC_SB_HEADER_SIZE;
}
