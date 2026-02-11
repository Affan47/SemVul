lzma_48631a (struct lzmastate *p, const char **old_ecx, uint32_t *old_edx, uint32_t *retval, char *src, uint32_t size)
{
	uint32_t copy1, copy2;
	uint32_t loc_esi, loc_edi, ret;
	const char *loc_ebx;

	copy1 = *old_edx;
	loc_edi = 0;
	loc_ebx = *old_ecx;
	*old_edx = 1;
	copy2 = (uint32_t)loc_edi;

	if (copy1 <= (uint32_t)loc_edi)
	{
		*retval = copy2;
		return 0;
	}

	do {
		loc_esi = *old_edx + *old_edx;
		*old_ecx = loc_esi + loc_ebx;
		if ((ret = lzma_486248 (p, old_ecx, src, size)) == 0xffffffff)
			return 0xffffffff;

		*old_edx = loc_esi + ret;

		ret <<= (loc_edi&0xff);
		copy2 |= ret;
		loc_edi++;
	} while (loc_edi < copy1);

	*retval = copy2;
	return 0;
}
