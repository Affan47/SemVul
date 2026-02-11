strncmpi(s1, s2, n)
    register const char *s1, *s2;
    register int n;
{
    register char t1, t2;

    while (n--) {
	if (!*s2) return (*s1 != 0);
	else if (!*s1) return -1;
	t1 = lowc(*s1++);
	t2 = lowc(*s2++);
	if (t1 != t2) return (t1 > t2) ? 1 : -1;
    }
    return 0;
}
