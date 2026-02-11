f_rm(int count, VALUE **vals)
{
	VALUE result;
	int force;
	int i;
	int j;


	result.v_subtype = V_NOSUBTYPE;


	if (!allow_write)
		return error_value(E_WRPERM);


	for (i=0; i < count; ++i) {
		if (vals[i]->v_type != V_STR)
			return error_value(E_RM1);
		if (vals[i]->v_str->s_str[0] == '\0')
			return error_value(E_RM1);
	}


	force = (strcmp(vals[0]->v_str->s_str, "-f") == 0);
	if (force) {
		--count;
		++vals;
	}


	for (i=0; i < count; ++i) {
		j = remove(vals[i]->v_str->s_str);
		if (!force && j < 0)
			return error_value(errno);
	}
	result.v_type = V_NULL;
	result.v_subtype = V_NOSUBTYPE;
	return result;
}
