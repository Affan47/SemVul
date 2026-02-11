can_eval(char *s)
{
	char *op;
	char *element1, *element2;
	char work[BUFSIZE];


	if ((FIRSTCHAR(s) == '(') &&
	    (count_chars(s, '(') == 1) &&
	    (count_chars(s, ')') == 1) &&
	    (strlen(s) > 2) &&
	    (LASTCHAR(s) == ')'))
		return TRUE;


	strcpy(work, s);

        if (!(op = strpbrk(work, "><+-&|*/%^")))
		return FALSE;

        element1 = &work[0];
        *op = NULLCHAR;
	element2 = op+1;

	if (!strlen(element1) || !strlen(element2))
		return FALSE;

	return TRUE;
}
