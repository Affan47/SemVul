f_ilog(VALUE *v1, VALUE *v2)
{
	VALUE res;

	if (v2->v_type != V_NUM || qisfrac(v2->v_num) || qiszero(v2->v_num) ||
			qisunit(v2->v_num))
		return error_value(E_ILOGB);

	switch(v1->v_type) {
	case V_NUM:
		res.v_num = qilog(v1->v_num, v2->v_num->num);
		break;
	case V_COM:
		res.v_num = c_ilog(v1->v_com, v2->v_num->num);
		break;
	default:
		return error_value(E_ILOG);
	}

	if (res.v_num == NULL)
		return error_value(E_LOGINF);

	res.v_type = V_NUM;
	res.v_subtype = V_NOSUBTYPE;
	return res;
}
