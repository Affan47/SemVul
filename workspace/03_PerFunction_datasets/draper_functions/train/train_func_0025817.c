regexp_exec(re, s, fname)
CONST reg_ex_t *re;
CONST char *s;
int fname;
{
	if (!re || (fname && skipdotfile && *s == '.')) return(0);

	return(_regexp_exec(re, s));
}
