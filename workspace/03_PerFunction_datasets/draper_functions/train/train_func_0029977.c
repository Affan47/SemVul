fz_union_rect(fz_rect a, fz_rect b)
{
	fz_rect r;
	if (fz_is_infinite_rect(a)) return a;
	if (fz_is_infinite_rect(b)) return b;
	if (fz_is_empty_rect(a)) return b;
	if (fz_is_empty_rect(b)) return a;
	r.x0 = fz_min(a.x0, b.x0);
	r.y0 = fz_min(a.y0, b.y0);
	r.x1 = fz_max(a.x1, b.x1);
	r.y1 = fz_max(a.y1, b.y1);
	return r;
}
