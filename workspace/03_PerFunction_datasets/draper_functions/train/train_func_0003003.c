bitmap_find_free_region(unsigned long *bitmap, int bits, int order)
{
	int pos, end;

	for (pos = 0 ; (end = pos + (1 << order)) <= bits; pos = end) {
		if (!__reg_op(bitmap, pos, order, REG_OP_ISFREE))
			continue;
		__reg_op(bitmap, pos, order, REG_OP_ALLOC);
		return pos;
	}
	return -ENOMEM;
}
