f_protect(int count, VALUE **vals)
{
	int i, depth;
	VALUE *v1, *v2, *v3;

	VALUE result;
	BOOL have_nblock;


	result.v_type = V_NULL;
	result.v_subtype = V_NOSUBTYPE;

	v1 = vals[0];
	have_nblock = (v1->v_type == V_NBLOCK);
	if (!have_nblock) {
		if (v1->v_type != V_ADDR)
			return error_value(E_PROTECT1);
		v1 = v1->v_addr;
	}
	if (count == 1) {
		result.v_type = V_NUM;
		if (have_nblock)
			result.v_num = itoq(v1->v_nblock->subtype);
		else
			result.v_num = itoq(v1->v_subtype);
		return result;
	}
	v2 = vals[1];
	if (v2->v_type == V_ADDR)
		v2 = v2->v_addr;
	if (v2->v_type != V_NUM||qisfrac(v2->v_num)||zge16b(v2->v_num->num))
		return error_value(E_PROTECT2);
	i = qtoi(v2->v_num);
	depth = 0;
	if (count > 2) {
		v3 = vals[2];
		if (v3->v_type == V_ADDR)
			v3 = v3->v_addr;
		if (v3->v_type != V_NUM || qisfrac(v3->v_num) ||
				qisneg(v3->v_num) || zge31b(v3->v_num->num))
			return error_value(E_PROTECT3);
		depth = qtoi(v3->v_num);
	}
	protecttodepth(v1, i, depth);
	return result;
}
