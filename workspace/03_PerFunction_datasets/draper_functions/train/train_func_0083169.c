choose_arena_hard(void)
{
	arena_t *ret;

	assert(__isthreaded);

#ifdef MALLOC_BALANCE

	SPRN(balance, (uint32_t)(uintptr_t)(pthread_self()));
#endif

	if (narenas > 1) {
#ifdef MALLOC_BALANCE
		unsigned ind;

		ind = PRN(balance, narenas_2pow);
		if ((ret = arenas[ind]) == NULL) {
			malloc_spin_lock(&arenas_lock);
			if ((ret = arenas[ind]) == NULL)
				ret = arenas_extend(ind);
			malloc_spin_unlock(&arenas_lock);
		}
#else
		malloc_spin_lock(&arenas_lock);
		if ((ret = arenas[next_arena]) == NULL)
			ret = arenas_extend(next_arena);
		next_arena = (next_arena + 1) % narenas;
		malloc_spin_unlock(&arenas_lock);
#endif
	} else
		ret = arenas[0];

	arenas_map = ret;

	return (ret);
}
