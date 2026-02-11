readIdentifier (vString *const name, const unsigned char *cp)
{
	const unsigned char *p;
	vStringClear (name);

	for (p = cp; *p != '\0' && *p != '(' && *p != ')' && !isspace (*p); p++)
		vStringPut (name, (int) *p);
	vStringTerminate (name);
}
