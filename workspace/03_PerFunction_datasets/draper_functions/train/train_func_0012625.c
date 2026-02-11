f_newerror(int count, VALUE **vals)
{
	char *str;
	int index;
	int errnum;

	str = NULL;
	if (count > 0 && vals[0]->v_type == V_STR)
		str = vals[0]->v_str->s_str;
	if (str == NULL || str[0] == '\0')
		str = "???";
	if (nexterrnum == E_USERDEF)
		initstr(&newerrorstr);
	index = findstr(&newerrorstr, str);
	if (index >= 0) {
		errnum = E_USERDEF + index;
	} else {
		if (nexterrnum == 32767)
			math_error("Too many new error values");
		errnum = nexterrnum++;
		addstr(&newerrorstr, str);
	}
	return error_value(errnum);
}
