wstrncpy(s1, s2, n)
wchar *s1, *s2;
int n;
{
	wchar	*ret = s1;

	while (n-- > 0 && (*s1++ = *s2++))
		;
	while (n-- > 0)
		*s1++ = 0;

	return ret;
}
