add_to_point_set(struct point_set *ps, int y, int x)
{
	ps->pts[ps->n].x = x;
	ps->pts[ps->n].y = y;
	ps->n++;
	if (ps->n >= ps->allocated) {
		ps->allocated *= 2;
		ps->pts = mem_realloc(ps->pts, sizeof(*(ps->pts)) * ps->allocated);
	}
}
