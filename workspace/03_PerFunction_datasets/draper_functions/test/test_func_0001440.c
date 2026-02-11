f_freopen(int count, VALUE **vals)
{
	VALUE result;
	FILEID id;
	char *mode;


	result.v_subtype = V_NOSUBTYPE;


	if (vals[0]->v_type != V_FILE)
		return error_value(E_FREOPEN1);
	if (vals[1]->v_type != V_STR)
		return error_value(E_FREOPEN2);
	mode = vals[1]->v_str->s_str;
	if ((*mode != 'r') && (*mode != 'w') && (*mode != 'a'))
		return error_value(E_FREOPEN2);
	if (mode[1] != '\0') {
		if (mode[1] != '+' && mode[1] != 'b')
			return error_value(E_FREOPEN2);
		if (mode[2] != '\0') {
			if ((mode[2] != '+' && mode[2] != 'b') ||
			    mode[1] == mode[2])
				return error_value(E_FOPEN2);
			if (mode[3] != '\0')
				return error_value(E_FREOPEN2);
		}
	}


	errno = 0;
	if (count == 2) {
		id = reopenid(vals[0]->v_file, mode, NULL);
	} else {
		if (vals[2]->v_type != V_STR)
			return error_value(E_FREOPEN3);
		id = reopenid(vals[0]->v_file, mode,
			vals[2]->v_str->s_str);
	}

	if (id == FILEID_NONE)
		return error_value(errno);
	result.v_type = V_NULL;
	return result;
}
