dynaprog(int l, int vpos, int **w)
{
	int *f[2], *curr, *prev, max, i;
	int8_t **b, *h = 0;
	uint32_t x, z = 1u<<(l-1), mask = (1u<<l) - 1;
	f[0] = calloc(z, sizeof(int));
	f[1] = calloc(z, sizeof(int));
	b = calloc(vpos, sizeof(void*));
	prev = f[0]; curr = f[1];

	for (i = 0; i < vpos; ++i) {
		int *wi = w[i], *tmp;
		int8_t *bi;
		bi = b[i] = calloc(z, 1);


		for (x = 0; x < z; ++x) {
			uint32_t y0, y1, xc;
			int c0, c1;
			xc = ~x&mask; y0 = x>>1; y1 = xc>>1;
			c0 = prev[y0] + wi[x] + wi[xc];
			c1 = prev[y1] + wi[x] + wi[xc];
			if (c0 > c1) bi[x] = 0, curr[x] = c0;
			else bi[x] = 1, curr[x] = c1;
		}
		tmp = prev; prev = curr; curr = tmp;
	}
	{
		uint32_t max_x = 0;
		int which = 0;
		h = calloc(vpos, 1);
		for (x = 0, max = 0, max_x = 0; x < z; ++x)
			if (prev[x] > max) max = prev[x], max_x = x;
		for (i = vpos - 1, x = max_x; i >= 0; --i) {
			h[i] = which? (~x&1) : (x&1);
			which = b[i][x]? !which : which;
			x = b[i][x]? (~x&mask)>>1 : x>>1;
		}
	}

	for (i = 0; i < vpos; ++i) free(b[i]);
	free(f[0]); free(f[1]); free(b);
	return h;
}
