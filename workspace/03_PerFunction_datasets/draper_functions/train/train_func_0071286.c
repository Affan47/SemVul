create_arenas(struct btt *btt)
{
	size_t remaining = btt->rawsize;
	size_t cur_off = 0;

	while (remaining) {
		struct arena_info *arena;
		size_t arena_size = min_t(u64, ARENA_MAX_SIZE, remaining);

		remaining -= arena_size;
		if (arena_size < ARENA_MIN_SIZE)
			break;

		arena = alloc_arena(btt, arena_size, btt->nlba, cur_off);
		if (!arena) {
			free_arenas(btt);
			return -ENOMEM;
		}
		btt->nlba += arena->external_nlba;
		if (remaining >= ARENA_MIN_SIZE)
			arena->nextoff = arena->size;
		else
			arena->nextoff = 0;
		cur_off += arena_size;
		list_add_tail(&arena->list, &btt->arena_list);
	}

	return 0;
}
