fz_stroke_bezier(struct sctx *s,
	float xa, float ya,
	float xb, float yb,
	float xc, float yc,
	float xd, float yd, int depth)
{
	float dmax;
	float xab, yab;
	float xbc, ybc;
	float xcd, ycd;
	float xabc, yabc;
	float xbcd, ybcd;
	float xabcd, yabcd;


	dmax = fz_abs(xa - xb);
	dmax = fz_max(dmax, fz_abs(ya - yb));
	dmax = fz_max(dmax, fz_abs(xd - xc));
	dmax = fz_max(dmax, fz_abs(yd - yc));
	if (dmax < s->flatness || depth >= MAX_DEPTH)
	{
		fz_point p;
		p.x = xd;
		p.y = yd;
		fz_stroke_lineto(s, p, 1);
		return;
	}

	xab = xa + xb;
	yab = ya + yb;
	xbc = xb + xc;
	ybc = yb + yc;
	xcd = xc + xd;
	ycd = yc + yd;

	xabc = xab + xbc;
	yabc = yab + ybc;
	xbcd = xbc + xcd;
	ybcd = ybc + ycd;

	xabcd = xabc + xbcd;
	yabcd = yabc + ybcd;

	xab *= 0.5f; yab *= 0.5f;
	xbc *= 0.5f; ybc *= 0.5f;
	xcd *= 0.5f; ycd *= 0.5f;

	xabc *= 0.25f; yabc *= 0.25f;
	xbcd *= 0.25f; ybcd *= 0.25f;

	xabcd *= 0.125f; yabcd *= 0.125f;

	fz_stroke_bezier(s, xa, ya, xab, yab, xabc, yabc, xabcd, yabcd, depth + 1);
	fz_stroke_bezier(s, xabcd, yabcd, xbcd, ybcd, xcd, ycd, xd, yd, depth + 1);
}
