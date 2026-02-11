dthstat(reg Dtdata_t* data, Dtstat_t* ds, reg int* count)
#else
static void dthstat(data, ds, count)
reg Dtdata_t*	data;
Dtstat_t*	ds;
reg int*	count;
#endif
{
	reg Dtlink_t*	t;
	reg int		n, h;

	for(h = data->ntab-1; h >= 0; --h)
	{	n = 0;
		for(t = data->htab[h]; t; t = t->right)
			n += 1;
		if(count)
			count[n] += 1;
		else if(n > 0)
		{	ds->dt_n += 1;
			if(n > ds->dt_max)
				ds->dt_max = n;
		}
	}
}
