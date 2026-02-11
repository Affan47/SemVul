getstr(str, n, fp)
    char *str;
    register int n;
    FILE *fp;
{
    register int c;
    register char *s;

    for (s = str; --n > 0 && (c = getc(fp)) != EOF; )
	if ((*s++ = c) == '\n')
	    break;
    return (s - str);
}
