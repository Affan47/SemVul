point_is_negative_of(const curve_point *p, const curve_point *q)
{

	if (!bn_is_equal(&(p->x), &(q->x))) {
		return 0;
	}


	if (bn_is_zero(&(p->y))) {
		return 0;
	}

	return !bn_is_equal(&(p->y), &(q->y));
}
