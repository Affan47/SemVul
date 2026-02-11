ast_hashtab_compare_shorts(const void *a, const void *b)
{
	short as = *((short *) a);
	short bs = *((short *) b);

	if (as < bs)
		return -1;

	return !(as == bs);
}
