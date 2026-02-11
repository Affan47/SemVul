intersection(point_t a, point_t b, vertex_t *vertex, pointf_t *ret)


{

	float s, t;

	float num, denom;
	point_t c = vertex->v;
	point_t d = CLIST_NEXT(vertex, entries)->v;

	denom = a.x * (float) (d.y - c.y) +
		b.x * (float) (c.y - d.y) +
		d.x * (float) (b.y - a.y) +
		c.x * (float) (a.y - b.y);

	if (denom == 0.0)

		return PF_ERROR;

	num = a.x * (float) (d.y - c.y) +
	      c.x * (float) (a.y - d.y) +
	      d.x * (float) (c.y - a.y);

	s = num / denom;

	num = -(a.x * (float) (c.y - b.y) +
		b.x * (float) (a.y - c.y) +
		c.x * (float) (b.y - a.y));

	t = num / denom;

	if ((0.0 <= s) && (s <= 1.0) && (0.0 < t) && (t < 1.0)) {

		ret->x = a.x + s * (b.x - a.x);
		ret->y = a.y + s * (b.y - a.y);
		return PF_OK;
	}

	return PF_ERROR;
}
