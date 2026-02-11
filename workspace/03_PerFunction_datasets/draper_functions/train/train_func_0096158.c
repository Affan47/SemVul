get_swapdev(ulong type, char *buf)
{
	unsigned int i, swap_info_len;
	ulong swap_info, swap_info_ptr, swap_file;
	ulong vfsmnt;

        if (!symbol_exists("nr_swapfiles"))
                error(FATAL, "nr_swapfiles doesn't exist in this kernel!\n");

        if (!symbol_exists("swap_info"))
                error(FATAL, "swap_info doesn't exist in this kernel!\n");

	swap_info_init();

        swap_info = symbol_value("swap_info");

	swap_info_len = (i = ARRAY_LENGTH(swap_info)) ?
		i : get_array_length("swap_info", NULL, 0);

        sprintf(buf, "(unknown swap location)");

	if (type >= swap_info_len)
		return buf;

	switch (vt->flags & (SWAPINFO_V1|SWAPINFO_V2))
	{
	case SWAPINFO_V1:
		swap_info += type * SIZE(swap_info_struct);
		fill_swap_info(swap_info);
		break;

	case SWAPINFO_V2:
		swap_info += type * sizeof(void *);
		if (!readmem(swap_info, KVADDR, &swap_info_ptr,
		    sizeof(void *), "swap_info pointer",
		    RETURN_ON_ERROR|QUIET))
			return buf;
		if (!swap_info_ptr)
			return buf;
		fill_swap_info(swap_info_ptr);
		break;
	}

	swap_file = ULONG(vt->swap_info_struct +
		OFFSET(swap_info_struct_swap_file));

        if (swap_file) {
		if (VALID_MEMBER(swap_info_struct_swap_vfsmnt)) {
			vfsmnt = ULONG(vt->swap_info_struct +
				OFFSET(swap_info_struct_swap_vfsmnt));
        		get_pathname(swap_file, buf, BUFSIZE, 1, vfsmnt);
                } else if (VALID_MEMBER (swap_info_struct_old_block_size)) {
                        get_pathname(file_to_dentry(swap_file),
                        	buf, BUFSIZE, 1, 0);
		} else {
        		get_pathname(swap_file, buf, BUFSIZE, 1, 0);
		}
        }

	return buf;
}
