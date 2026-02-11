FullLine(F, p)
    register FILE	*F;
    register char	*p;
{
    register char	*dest;
    OFFSET_T		l;
    register int	c;
    register int	i;

    for (dest = (char *)&l, i = sizeof l; --i >= 0; )
	*dest++ = *p++;
    if (fseek(F, l, SEEK_SET) == -1) {
	(void)fprintf(stderr, "Can't seek to %ld, %s\n", l, strerror(errno));
	exit(1);
    }

    while ((c = getc(F)) != EOF && c != '\n')
	(void)putchar(c);
    (void)putchar('\n');
}
