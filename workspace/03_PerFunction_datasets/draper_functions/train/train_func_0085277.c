do_split_allocation(struct block_allocation *alloc, u32 len)
{
	struct region *reg = alloc->list.iter;
	struct region *new;
	struct region *tmp;

	while (reg && len >= reg->len) {
		len -= reg->len;
		reg = reg->next;
	}

	if (reg == NULL && len > 0)
		return NULL;

	if (len > 0) {
		new = malloc(sizeof(struct region));

		new->bg = reg->bg;
		new->block = reg->block + len;
		new->len = reg->len - len;
		new->next = reg->next;
		new->prev = reg;

		reg->next = new;
		reg->len = len;

		tmp = alloc->list.iter;
		alloc->list.iter = new;
		return tmp;
	} else {
		return reg;
	}
}
