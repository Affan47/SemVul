insert_refcount_el(ext2_refcount_t refcount,
						 blk_t blk, int pos)
{
	struct ea_refcount_el 	*el;
	errcode_t		retval;
	blk_t			new_size = 0;
	int			num;

	if (refcount->count >= refcount->size) {
		new_size = refcount->size + 100;
#ifdef DEBUG
		printf("Reallocating refcount %d entries...\n", new_size);
#endif
		retval = ext2fs_resize_mem((size_t) refcount->size *
					   sizeof(struct ea_refcount_el),
					   (size_t) new_size *
					   sizeof(struct ea_refcount_el),
					   &refcount->list);
		if (retval)
			return 0;
		refcount->size = new_size;
	}
	num = (int) refcount->count - pos;
	if (num < 0)
		return 0;
	if (num) {
		memmove(&refcount->list[pos+1], &refcount->list[pos],
			sizeof(struct ea_refcount_el) * num);
	}
	refcount->count++;
	el = &refcount->list[pos];
	el->ea_count = 0;
	el->ea_blk = blk;
	return el;
}
