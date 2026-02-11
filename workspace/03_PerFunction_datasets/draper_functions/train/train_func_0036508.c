isw_read_extended(struct lib_context *lc, struct dev_info *di,
		  struct isw **isw, uint64_t * isw_sboffset, size_t * size)
{
	struct isw *isw_tmp;

	size_t blocks = div_up((*isw)->mpb_size, ISW_DISK_BLOCK_SIZE);


	*size = blocks * ISW_DISK_BLOCK_SIZE;
	*isw_sboffset -= *size - ISW_DISK_BLOCK_SIZE;

	if ((isw_tmp = alloc_private(lc, handler, *size))) {

		memcpy(isw_tmp, *isw, ISW_DISK_BLOCK_SIZE);


		if (blocks > 1 &&
		    !read_file(lc, handler, di->path,
			(void *) (((uint8_t*)isw_tmp) + ISW_DISK_BLOCK_SIZE),
			*size - ISW_DISK_BLOCK_SIZE, *isw_sboffset)) {
			dbg_free(isw_tmp);
			isw_tmp = NULL;
		}
	} else
		return 0;

	dbg_free(*isw);
	*isw = isw_tmp;
	return *isw ? 1 : 0;
}
