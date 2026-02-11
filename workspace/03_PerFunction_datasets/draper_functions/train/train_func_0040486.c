f_fseek(int count, VALUE **vals)
{
	VALUE result;
	int whence;
	int i;


	result.v_subtype = V_NOSUBTYPE;


	errno = 0;
	if (vals[0]->v_type != V_FILE)
		return error_value(E_FSEEK1);
	if (vals[1]->v_type != V_NUM || qisfrac(vals[1]->v_num))
		return error_value(E_FSEEK2);
	if (count == 2) {
		whence = 0;
	} else {
		if (vals[2]->v_type != V_NUM || qisfrac(vals[2]->v_num) ||
			qisneg(vals[2]->v_num))
			return error_value(E_FSEEK2);
		if (vals[2]->v_num->num.len > 1)
			return error_value (E_FSEEK2);
		whence = (int)(unsigned int)(vals[2]->v_num->num.v[0]);
		if (whence > 2)
			return error_value (E_FSEEK2);
	}

	i = fseekid(vals[0]->v_file, vals[1]->v_num->num, whence);
	result.v_type = V_NULL;
	if (i == EOF)
		return error_value(errno);
	if (i < 0)
		return error_value(E_FSEEK3);
	return result;
}
