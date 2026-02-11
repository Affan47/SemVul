agp_find_max(void)
{
	long memory, index, result;

#if PAGE_SHIFT < 20
	memory = totalram_pages >> (20 - PAGE_SHIFT);
#else
	memory = totalram_pages << (PAGE_SHIFT - 20);
#endif
	index = 1;

	while ((memory > maxes_table[index].mem) && (index < 8))
		index++;

	result = maxes_table[index - 1].agp +
	   ( (memory - maxes_table[index - 1].mem)  *
	     (maxes_table[index].agp - maxes_table[index - 1].agp)) /
	   (maxes_table[index].mem - maxes_table[index - 1].mem);

	result = result << (20 - PAGE_SHIFT);
	return result;
}
