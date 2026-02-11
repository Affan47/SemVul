zone_eq(const void *a, const void *b)
{
	const zone_t *za = a, *zb = b;

	return za->zn_size == zb->zn_size && za->zn_stid == zb->zn_stid &&
		za->private == zb->private;
}
