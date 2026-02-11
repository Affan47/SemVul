f_prompt(VALUE *vp)
{
	VALUE result;
	char *cp;
	char *newcp;
	size_t len;


	result.v_type = V_STR;
	result.v_subtype = V_NOSUBTYPE;

	openterminal();
	printvalue(vp, PRINT_SHORT);
	math_flush();
	cp = nextline();
	closeinput();
	if (cp == NULL) {
		result.v_type = V_NULL;
		return result;
	}
	if (*cp == '\0') {
		result.v_str = slink(&_nullstring_);
		return result;
	}
	len = strlen(cp);
	newcp = (char *) malloc(len + 1);
	if (newcp == NULL) {
		math_error("Cannot allocate string");

	}
	strncpy(newcp, cp, len+1);
	result.v_str = makestring(newcp);
	return result;
}
