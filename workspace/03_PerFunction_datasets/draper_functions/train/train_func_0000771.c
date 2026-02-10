lzma_upack_esi_54(struct lzmastate *p, uint32_t old_eax, uint32_t *old_ecx, char **old_edx, uint32_t *retval, char *bs, uint32_t bl)
{
	uint32_t ret, loc_eax = old_eax;

	*old_ecx = ((*old_ecx)&0xffffff00)|8;
	ret = lzma_upack_esi_00 (p, *old_edx, bs, bl);
	*old_edx = ((*old_edx) + 4);
	loc_eax = (loc_eax&0xffffff00)|1;
	if (ret)
	{
		ret = lzma_upack_esi_00 (p, *old_edx, bs, bl);
		loc_eax |= 8;
		if (ret)
		{
			*old_ecx <<= 5;
			loc_eax = 0x11;
		}
	}
	ret = loc_eax;
	if (lzma_upack_esi_50(p, 1, *old_ecx, old_edx, *old_edx + (loc_eax << 2), &loc_eax, bs, bl) == 0xffffffff)
		return 0xffffffff;

	*retval = ret + loc_eax;
	return 0;
}
