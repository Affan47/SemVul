wf_find_point(WaveVar *iv, double ival)
{
	WDataSet *ds = iv->wds;
	double cval;
	int a, b;
	int n = 0;

	a = 0;
	b = iv->wv_nvalues - 1;
	if(ival >= ds->max)
		return b;
	while(a+1 < b) {
		cval = wds_get_point(ds, (a+b)/2);

		if(ival < cval)
			b = (a+b)/2;
		else
			a = (a+b)/2;


		g_assert(n++ < 32);
	}
	return a;
}
