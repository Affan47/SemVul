SubstValue(char c, char **s, int *i)
#else
SubstValue(c, s, i)
    char c;
    char **s;
    int *i;
#endif
{
    int retval = 0;

    if (s != (char **)0) {
	CONFIG *pc;
	if (substData->data == (void *)0)
	    return 0;

	pc = (CONFIG *)(substData->data);
	if (c == 'u') {
	    (*s) = pc->username;
	    retval = 1;
	} else if (c == 'c') {
	    (*s) = pc->console;
	    retval = 1;
	}
    }

    return retval;
}
