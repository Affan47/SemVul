ignore_init_rec(IGNORE_REC *rec)
{
#ifdef HAVE_REGEX_H
	if (rec->regexp_compiled) regfree(&rec->preg);
	rec->regexp_compiled = !rec->regexp || rec->pattern == NULL ? FALSE :
		regcomp(&rec->preg, rec->pattern,
			REG_EXTENDED|REG_ICASE|REG_NOSUB) == 0;
#endif
}
