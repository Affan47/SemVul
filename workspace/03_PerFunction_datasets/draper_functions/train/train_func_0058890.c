hdup_ok_char(char *check)
{


	char * cp;

	for (cp = check; *(cp += strspn(cp, ok_chars));  ) {
		VERBOSE("%s: %s", "sanitizing", check);
		*cp = '_';
	}

	return 0;
}
