tbm_comparator(const void *left, const void *right)
{
	BlockNumber l = (*((const PagetableEntry **) left))->blockno;
	BlockNumber r = (*((const PagetableEntry **) right))->blockno;

	if (l < r)
		return -1;
	else if (l > r)
		return 1;
	return 0;
}
