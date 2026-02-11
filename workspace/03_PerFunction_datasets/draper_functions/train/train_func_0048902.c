strscan(char *s, int count, VALUE **vals)
{
	char	ch, chtmp;
	char	*s0;
	int	n = 0;
	VALUE	val, result;
	VALUE	*var;


	val.v_subtype = V_NOSUBTYPE;
	result.v_subtype = V_NOSUBTYPE;

	val.v_type = V_STR;
	while (*s != '\0') {
		s--;
		while ((ch = *++s)) {
			if (!isspace((int)ch))
				break;
		}
		if (ch == '\0' || count-- == 0)
			return n;
		s0 = s;
		while ((ch = *++s)) {
			if (isspace((int)ch))
				break;
		}
		chtmp = ch;
		*s = '\0';
		n++;
		val.v_str = makenewstring(s0);
		result = f_eval(&val);
		var = *vals++;
		if (var->v_type == V_ADDR) {
			var = var->v_addr;
			freevalue(var);
			*var = result;
		}
		*s = chtmp;
	}
	return n;
}
