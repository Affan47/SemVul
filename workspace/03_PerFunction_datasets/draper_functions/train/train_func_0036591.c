get_icount_el(ext2_icount_t icount,
					    ext2_ino_t ino, int create)
{
	float	range;
	int	low, high, mid;
	ext2_ino_t	lowval, highval;

	if (!icount || !icount->list)
		return 0;

	if (create && ((icount->count == 0) ||
		       (ino > icount->list[(unsigned)icount->count-1].ino))) {
		return insert_icount_el(icount, ino, (unsigned) icount->count);
	}
	if (icount->count == 0)
		return 0;

	if (icount->cursor >= icount->count)
		icount->cursor = 0;
	if (ino == icount->list[icount->cursor].ino)
		return &icount->list[icount->cursor++];
#if 0
	printf("Non-cursor get_icount_el: %u\n", ino);
#endif
	low = 0;
	high = (int) icount->count-1;
	while (low <= high) {
#if 0
		mid = (low+high)/2;
#else
		if (low == high)
			mid = low;
		else {

			lowval = icount->list[low].ino;
			highval = icount->list[high].ino;

			if (ino < lowval)
				range = 0;
			else if (ino > highval)
				range = 1;
			else {
				range = ((float) (ino - lowval)) /
					(highval - lowval);
				if (range > 0.9)
					range = 0.9;
				if (range < 0.1)
					range = 0.1;
			}
			mid = low + ((int) (range * (high-low)));
		}
#endif
		if (ino == icount->list[mid].ino) {
			icount->cursor = mid+1;
			return &icount->list[mid];
		}
		if (ino < icount->list[mid].ino)
			high = mid-1;
		else
			low = mid+1;
	}


	if (create)
		return insert_icount_el(icount, ino, low);
	return 0;
}
