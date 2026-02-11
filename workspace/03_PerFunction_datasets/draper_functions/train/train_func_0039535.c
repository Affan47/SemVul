ast_callerid_split(const char *buf, char *name, int namelen, char *num, int numlen)
{
	char *tmp;
	char *l = NULL, *n = NULL;

	tmp = ast_strdupa(buf);
	ast_callerid_parse(tmp, &n, &l);
	if (n)
		ast_copy_string(name, n, namelen);
	else
		name[0] = '\0';
	if (l) {
		ast_shrink_phone_number(l);
		ast_copy_string(num, l, numlen);
	} else
		num[0] = '\0';
	return 0;
}
