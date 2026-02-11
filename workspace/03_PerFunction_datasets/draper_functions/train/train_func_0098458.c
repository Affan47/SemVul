cli_htu32_init(struct cli_htu32 *s, size_t capacity, mpool_t *mempool)
{
	if(!s)
		return CL_ENULLARG;

	PROFILE_INIT(s);

	capacity = nearest_power(capacity);
	s->htable = mpool_calloc(mempool, capacity, sizeof(*s->htable));
	if(!s->htable)
		return CL_EMEM;
	s->capacity = capacity;
	s->used = 0;
	s->maxfill = 8*capacity/10;
	return 0;
}
