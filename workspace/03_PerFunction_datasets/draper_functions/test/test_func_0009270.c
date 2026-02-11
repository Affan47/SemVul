diff_from_target(void *target)
{
	double d64, dcut64;

	d64 = truediffone;
	dcut64 = le256todouble(target);
	if (unlikely(!dcut64))
		dcut64 = 1;
	return d64 / dcut64;
}
