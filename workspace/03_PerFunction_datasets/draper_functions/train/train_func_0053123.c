cmp_device(gconstpointer a, gconstpointer b)
{
	const struct deviceinfo *d = a;
	const struct btd_device *dev = b;

	if (dev == d->dev)
		return 0;

	return -1;
}
