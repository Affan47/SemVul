do_input(char *alias,
		     kernel_ulong_t *arr, unsigned int min, unsigned int max)
{
	unsigned int i;

	for (i = min / BITS_PER_LONG; i < max / BITS_PER_LONG + 1; i++)
		arr[i] = TO_NATIVE(arr[i]);
	for (i = min; i < max; i++)
		if (arr[i / BITS_PER_LONG] & (1L << (i%BITS_PER_LONG)))
			sprintf(alias + strlen(alias), "%X,*", i);
}
