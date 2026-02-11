mem_pool_validate(

	mem_pool_t*	pool)
{
	mem_area_t*	area;
	mem_area_t*	buddy;
	ulint		free;
	ulint		i;

	mem_pool_mutex_enter(pool);

	free = 0;

	for (i = 0; i < 64; i++) {

		UT_LIST_VALIDATE(free_list, mem_area_t, pool->free_list[i],
				 (void) 0);

		area = UT_LIST_GET_FIRST(pool->free_list[i]);

		while (area != NULL) {
			ut_a(mem_area_get_free(area));
			ut_a(mem_area_get_size(area) == ut_2_exp(i));

			buddy = mem_area_get_buddy(area, ut_2_exp(i), pool);

			ut_a(!buddy || !mem_area_get_free(buddy)
			     || (ut_2_exp(i) != mem_area_get_size(buddy)));

			area = UT_LIST_GET_NEXT(free_list, area);

			free += ut_2_exp(i);
		}
	}

	ut_a(free + pool->reserved == pool->size);

	mem_pool_mutex_exit(pool);

	return(TRUE);
}
