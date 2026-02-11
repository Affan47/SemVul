get_num(char str[])
{
    int count = 0;

    token[t_num].is_token = FALSE;
    token[t_num].l_val.type = INTGR;
    while (isdigit((unsigned char) str[count]))
	count++;
    if (str[count] == '.') {
	token[t_num].l_val.type = CMPLX;

	while (isdigit((unsigned char) str[++count]));

    }
    if (str[count] == 'e' || str[count] == 'E') {
	token[t_num].l_val.type = CMPLX;
	count++;
	if (str[count] == '-' || str[count] == '+')
	    count++;
	if (!isdigit((unsigned char) str[count])) {
	    token[t_num].start_index += count;
	    int_error(t_num, "expecting exponent");
	}
	while (isdigit((unsigned char) str[++count]));
    }
    if (token[t_num].l_val.type == INTGR) {
	long lval;
	char *endptr;
	errno = 0;
	lval = strtol(str, &endptr, 0);
	if (!errno &&
	   ((token[t_num].l_val.v.int_val = lval) == lval))
		return(endptr-str);
	int_warn(t_num, "integer overflow; changing to floating point");
	token[t_num].l_val.type = CMPLX;

    }
    token[t_num].l_val.v.cmplx_val.imag = 0.0;
    token[t_num].l_val.v.cmplx_val.real = atof(str);
    return (count);
}
