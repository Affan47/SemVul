gfill(double c[], int st, int n, int connect[])
{
	int i;
	if (!m->active) return;
	for (i=0; i<2*n; i++) if (fabs(c[i])>10000.0) return;
	commandwrite(30);
	shortwrite(n);
	for (i=0; i<n; i++) {
		longwrite(c[2*i]);
		longwrite(c[2*i+1]);
		shortwrite(connect[i]);
	}
	shortwrite(st);
	if (!m->recording && m->device && m->device->fill)
		m->device->fill(m->device->data,c,st,n,connect);
}
