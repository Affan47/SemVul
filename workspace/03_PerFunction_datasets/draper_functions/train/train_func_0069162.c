set_bounds(__isl_take isl_set *set)
{
	unsigned nparam;
	int i, r;
	isl_point *pt, *pt2;
	isl_set *box;

	nparam = isl_set_dim(set, isl_dim_param);
	r = nparam >= 8 ? 5 : nparam >= 5 ? 15 : 50;

	pt = isl_set_sample_point(isl_set_copy(set));
	pt2 = isl_point_copy(pt);

	for (i = 0; i < nparam; ++i) {
		pt = isl_point_add_ui(pt, isl_dim_param, i, r);
		pt2 = isl_point_sub_ui(pt2, isl_dim_param, i, r);
	}

	box = isl_set_box_from_points(pt, pt2);

	return isl_set_intersect(set, box);
}
