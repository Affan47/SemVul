syslinux_memmap_type(struct syslinux_memmap *list,
						addr_t start, addr_t len)
{
    addr_t last, llast;

    last = start + len - 1;

    while (list->type != SMT_END) {
	llast = list->next->start - 1;
	if (list->start <= start) {
	    if (llast >= last)
		return list->type;
	    else if (llast >= start)
		return SMT_ERROR;
	}
	list = list->next;
    }

    return SMT_ERROR;
}
