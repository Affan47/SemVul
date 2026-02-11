f_strncpy(VALUE *v1, VALUE *v2, VALUE *v3)
{
	VALUE result;
	long num;


	result.v_subtype = V_NOSUBTYPE;

	if (v1->v_type != V_STR || v2->v_type != V_STR ||
		v3->v_type != V_NUM || qisfrac(v3->v_num) || qisneg(v3->v_num))
			return error_value(E_STRNCPY);
	if (zge31b(v3->v_num->num))
		num = v2->v_str->s_len;
	else
		num = qtoi(v3->v_num);
	result.v_str = stringncpy(v1->v_str, v2->v_str, num);
	result.v_type = V_STR;
	return result;
}
