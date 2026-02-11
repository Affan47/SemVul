readIdentifier (lexingState * st)
{
	const unsigned char *p;
	vStringClear (st->name);


	if (isAlpha (*st->cp) || *st->cp == '_')
		vStringPut (st->name, (int) *st->cp);


	for (p = st->cp + 1; isIdent (*p); p++)
		vStringPut (st->name, (int) *p);

	st->cp = p;

	vStringTerminate (st->name);
}
