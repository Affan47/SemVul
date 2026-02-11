f_segment(int count, VALUE **vals)
{
	VALUE *vp;
	long n1, n2;
	VALUE result;


	result.v_subtype = V_NOSUBTYPE;

	vp = vals[1];

	if (vp->v_type != V_NUM || qisfrac(vp->v_num) || zge31b(vp->v_num->num))
		return error_value(E_SEG2);
	n1 = qtoi(vp->v_num);
	n2 = n1;
	if (count == 3) {
		vp = vals[2];
		if (vp->v_type != V_NUM || qisfrac(vp->v_num) ||
			zge31b(vp->v_num->num))
				return error_value(E_SEG3);
		n2 = qtoi(vp->v_num);
	}
	vp = vals[0];
	result.v_type = vp->v_type;
	switch (vp->v_type) {
		case V_LIST:
			result.v_list = listsegment(vp->v_list, n1, n2);
			return result;
		case V_STR:
			result.v_str = stringsegment(vp->v_str, n1, n2);
			if (result.v_str == NULL)
				return error_value(E_STRSEG);
			return result;
		default:
			return error_value(E_SEG1);
	}
}
