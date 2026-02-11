strlcmp(char *ap, char *bp)
{
	int a, b;
	for (;;) {
		a = tolower(*ap);
		b = tolower(*bp);
		if (a != b)
			return (a - b);
		if (a == 0)
			return 0;
		ap++;
		bp++;
	}
}
