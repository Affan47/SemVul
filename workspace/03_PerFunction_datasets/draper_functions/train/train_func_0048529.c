GMT_copy_to_shore_path (double *lon, double *lat, struct GMT_SHORE *s, GMT_LONG id)
{
	GMT_LONG i;
	for (i = 0; i < (GMT_LONG)s->seg[id].n; i++)
		GMT_shore_to_degree (s, s->seg[id].dx[i], s->seg[id].dy[i], &lon[i], &lat[i]);
	return (s->seg[id].n);
}
