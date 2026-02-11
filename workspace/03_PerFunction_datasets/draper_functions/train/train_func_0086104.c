compare_patches (gconstpointer a, gconstpointer b)
{
	int i, j;

	i = (*(MonoJumpInfo**)a)->ip.i;
	j = (*(MonoJumpInfo**)b)->ip.i;

	if (i < j)
		return -1;
	else
		if (i > j)
			return 1;
	else
		return 0;
}
