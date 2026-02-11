cmp_all(void *binary, int count)
{
	int index;

	for (index = 0; index < count; index++)
	if (buffer[index].is_long) {
		if (*(unsigned ARCH_WORD *)binary ==
		    buffer[index].aligned.binary[0])
			return 1;
	} else {
		if (((unsigned ARCH_WORD *)binary)[2] ==
		    (buffer[index].aligned.binary[0] & TOTAL_BINARY_MASK))
			return 1;
	}

	return 0;
}
