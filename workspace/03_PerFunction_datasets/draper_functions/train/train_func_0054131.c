cob_get_environment (cob_field *envname, cob_field *envval)
{
	const char	*p;
	char		*buff;

	if (envname->size < COB_SMALL_BUFF) {
		buff = cob_malloc (COB_SMALL_BUFF);
		cob_field_to_string (envname, buff);
		p = getenv (buff);
		if (!p) {
			cob_set_exception (COB_EC_IMP_ACCEPT);
			p = " ";
		}
		cob_memcpy (envval, (ucharptr)p, (int) strlen (p));
		free (buff);
	} else {
		cob_set_exception (COB_EC_IMP_ACCEPT);
		p = " ";
		cob_memcpy (envval, (ucharptr)p, (int) strlen (p));
	}
}
