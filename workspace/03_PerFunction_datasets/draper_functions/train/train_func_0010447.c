getid(char *buf)
{
	int type;

	type = gettoken();
	if (iskeyword(type)) {
		scanerror(T_NULL, "Reserved keyword used as symbol name");
		type = T_SYMBOL;
		*buf = '\0';
		return FALSE;
	}
	if (type != T_SYMBOL) {
		rescantoken();
		scanerror(T_NULL, "Symbol name expected");
		*buf = '\0';
		return FALSE;
	}
	strncpy(buf, tokensymbol(), SYMBOLSIZE);
	buf[SYMBOLSIZE] = '\0';
	return TRUE;
}
