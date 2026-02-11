GMT_free_polygons (struct GMT_GSHHS_POL *p, GMT_LONG n)
{
	GMT_LONG k;
	for (k = 0; k < n; k++) {
		GMT_free ((void *)p[k].lon);
		GMT_free ((void *)p[k].lat);
	}
}
