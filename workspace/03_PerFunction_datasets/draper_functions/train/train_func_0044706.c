f_sort(VALUE *val)
{
	VALUE res;

	res.v_type = val->v_type;
	res.v_subtype = val->v_subtype;
	switch (val->v_type) {
		case V_MAT:
			res.v_mat = matcopy(val->v_mat);
			matsort(res.v_mat);
			break;
		case V_LIST:
			res.v_list = listcopy(val->v_list);
			listsort(res.v_list);
			break;
		default:
			math_error("Bad argument type for sort");

	}
	return res;
}
