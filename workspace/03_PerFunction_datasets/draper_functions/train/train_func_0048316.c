strncasecmp_pl(const char *cs, const char *ct , size_t count)
{
	register signed char __res = 0;
#if USE_UNICODE
	wchar_t *wc1 = xmalloc((count+1) * sizeof(wchar_t));
	wchar_t *wc2 = xmalloc((count+1) * sizeof(wchar_t));
	wchar_t *p;
	int n1 = mbsrtowcs(wc1, &cs, count, NULL);
	int n2 = mbsrtowcs(wc2, &ct, count, NULL);

	wc1[n1<0 ? 0 : n1] = 0;
	wc2[n2<0 ? 0 : n2] = 0;

	for(p=wc1; *p; p++) *p = towlower(*p);
	for(p=wc2; *p; p++) *p = towlower(*p);

	__res = wcscoll(wc1, wc2);

	xfree(wc1);
	xfree(wc2);
#else
	while (count) {
		if ((__res = tolower_pl(*cs) - tolower_pl(*ct++)) != 0 || !*cs++)
			break;
		count--;
	}
#endif
	return __res;
}
