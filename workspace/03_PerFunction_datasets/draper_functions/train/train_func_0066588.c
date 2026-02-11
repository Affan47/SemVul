bitmask_abs_to_rel_pos(const struct bitmask *bmp, unsigned int n)
{
	unsigned int i;
	unsigned int w = 0;

	if (!_getbit(bmp, n))
		return bmp->size;

	for (i = 0; i < n; i++)
		if (_getbit(bmp, i))
			w++;
	return w;
}
