test_overlap(const struct inst *a, const struct inst *b,
    const struct shape *other, enum allow_overlap allow)
{
	struct coord min, max;
	unit_type h, w, r;
	int rounded;

	min = a->base;
	switch (a->obj->type) {
	case ot_pad:
		max = a->u.pad.other;
		rounded = a->obj->u.pad.rounded;
		break;
	case ot_hole:
		max = a->u.hole.other;
		rounded = 1;
		break;
	default:
		abort();
	}
	sort_coord(&min, &max);

	h = max.y-min.y;
	w = max.x-min.x;

	if (!rounded)
		return do_rect(b, other, min.x, min.y, w, h, allow);

	if (h > w) {
		r = w/2;
		return do_circle(b, other, min.x+r, max.y-r, r, allow) ||
		    do_rect(b, other, min.x, min.y+r, w, h-2*r, allow) ||
		    do_circle(b, other, min.x+r, min.y+r, r, allow);
	} else {
		r = h/2;
		return do_circle(b, other, min.x+r, min.y+r, r, allow) ||
		    do_rect(b, other, min.x+r, min.y, w-2*r, h, allow) ||
		    do_circle(b, other, max.x-r, min.y+r, r, allow);
	}
}
