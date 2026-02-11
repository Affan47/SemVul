overlaps(sector_t s1, sector_t l1, sector_t s2, sector_t l2)
{

	if (s1+l1 <= s2)
		return 0;
	if (s2+l2 <= s1)
		return 0;
	return 1;
}
