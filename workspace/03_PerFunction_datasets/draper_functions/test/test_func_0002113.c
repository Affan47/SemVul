dbg_move(const char *name, int anchor, const char *dest)
{
	struct vec *to, *vec;
	struct obj *obj;
	struct vec **anchors[3];
	int n_anchors;

	to = find_vec(curr_frame, dest);
	if (!to) {
		yyerrorf("unknown vector \"%s\"", dest);
		return 0;
	}
	vec = find_vec(curr_frame, name);
	if (vec) {
		if (anchor) {
			yyerrorf("invalid anchor (%d > 0)", anchor);
			return 0;
		}
		vec->base = to;
		return 1;
	}
	obj = find_obj(curr_frame, name);
	if (!obj) {
		yyerrorf("unknown item \"%s\"", name);
		return 0;
	}
	n_anchors = obj_anchors(obj, anchors);
	if (anchor >= n_anchors) {
		yyerrorf("invalid anchor (%d > %d)", anchor, n_anchors-1);
		return 0;
	}
	*anchors[anchor] = to;
	return 1;
}
