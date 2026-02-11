syslinux_memmap_find(struct syslinux_memmap *list,
			 enum syslinux_memmap_types type,
			 addr_t * start, addr_t * len, addr_t align)
{
    addr_t min_start = *start;
    addr_t min_len = *len;

    while (list->type != SMT_END) {
	if (list->type == type) {
	    addr_t xstart, xlen;
	    xstart = min_start > list->start ? min_start : list->start;
	    xstart = ALIGN_UP(xstart, align);

	    if (xstart < list->next->start) {
		xlen = list->next->start - xstart;
		if (xlen >= min_len) {
		    *start = xstart;
		    *len = xlen;
		    return 0;
		}
	    }
	}
	list = list->next;
    }

    return -1;
}
