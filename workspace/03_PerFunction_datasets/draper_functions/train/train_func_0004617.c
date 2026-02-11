end_new_raw_vec(struct inst *from, struct coord to)
{
	struct vec *vec;
	struct coord pos;

	vec = new_vec(from);
	pos = inst_get_point(from);
	to = gridify(pos, to);
	switch (curr_unit) {
	case curr_unit_mm:
	case curr_unit_auto:
		vec->x = new_num(make_mm(units_to_mm(to.x-pos.x)));
		vec->y = new_num(make_mm(units_to_mm(to.y-pos.y)));
		break;
	case curr_unit_mil:
		vec->x = new_num(make_mil(units_to_mil(to.x-pos.x)));
		vec->y = new_num(make_mil(units_to_mil(to.y-pos.y)));
		break;
	default:
		abort();
	}
	return 1;
}
