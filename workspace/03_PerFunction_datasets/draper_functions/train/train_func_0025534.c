free_gcr3_tbl_level2(u64 *tbl)
{
	u64 *ptr;
	int i;

	for (i = 0; i < 512; ++i) {
		if (!(tbl[i] & GCR3_VALID))
			continue;

		ptr = __va(tbl[i] & PAGE_MASK);

		free_gcr3_tbl_level1(ptr);
	}
}
