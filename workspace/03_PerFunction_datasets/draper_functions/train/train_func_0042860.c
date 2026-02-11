offset_vec(struct coord a, struct coord b,
    const struct inst *self)
{
	struct coord res;
	double f;

	res.x = a.y-b.y;
	res.y = b.x-a.x;
	if (res.x == 0 && res.y == 0)
		return res;
	f = self->u.meas.offset/hypot(res.x, res.y);
	res.x *= f;
	res.y *= f;
	return res;
}
