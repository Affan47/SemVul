smsorte_test(void *array, void *copy, size_t cnt, size_t isize, size_t loops)
{
	smsort_less_t less = get_less_routine(isize);
	smsort_swap_t swap = get_swap_routine(isize);
	size_t len = cnt * isize;

	do {
		memcpy(copy, array, len);
		smsort_ext(copy, 0, cnt, less, swap);
	} while (--loops > 0);
}
