mct_encode_real(
		int* restrict c0,
		int* restrict c1,
		int* restrict c2,
		int n)
{
	int i;
	for(i = 0; i < n; ++i) {
		int r = c0[i];
		int g = c1[i];
		int b = c2[i];
		int y =  fix_mul(r, 2449) + fix_mul(g, 4809) + fix_mul(b, 934);
		int u = -fix_mul(r, 1382) - fix_mul(g, 2714) + fix_mul(b, 4096);
		int v =  fix_mul(r, 4096) - fix_mul(g, 3430) - fix_mul(b, 666);
		c0[i] = y;
		c1[i] = u;
		c2[i] = v;
	}
}
