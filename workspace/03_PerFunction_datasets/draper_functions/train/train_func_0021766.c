gfs2_special_add(struct special_blocks *blocklist, uint64_t block)
{
	struct special_blocks *b;

	b = malloc(sizeof(struct special_blocks));
	if (b) {
		memset(b, 0, sizeof(*b));
		b->block = block;
		osi_list_add_prev(&b->list, &blocklist->list);
	}
}
