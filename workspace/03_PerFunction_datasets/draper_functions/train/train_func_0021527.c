bitmask_intersects(const struct bitmask *bmp1, const struct bitmask *bmp2)
{
	unsigned int i;
	for (i = 0; i < bmp1->size; i++)
		if (_getbit(bmp1, i) & _getbit(bmp2, i))
			return 1;
	return 0;
}
