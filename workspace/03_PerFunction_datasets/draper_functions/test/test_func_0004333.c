compare_start(struct fdisk_context *cxt,
			 const void *x, const void *y)
{


	unsigned int i = *(int *) x;
	unsigned int j = *(int *) y;
	unsigned int a = sgi_get_start_sector(cxt, i);
	unsigned int b = sgi_get_start_sector(cxt, j);
	unsigned int c = sgi_get_num_sectors(cxt, i);
	unsigned int d = sgi_get_num_sectors(cxt, j);

	if (a == b)
		return (d > c) ? 1 : (d == c) ? 0 : -1;
	return (a > b) ? 1 : -1;
}
