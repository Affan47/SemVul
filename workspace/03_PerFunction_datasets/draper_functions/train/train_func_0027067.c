addroman(s, buf)
CONST char *s, *buf;
{
#ifdef	DEP_FILECONV
	char tmp[R_MAXKANA * 3 + 1];
#endif
	char str[R_MAXROMAN + 1];
	u_short kbuf[R_MAXKANA];
	int i, j, len;

	initroman();

	if (!s) return(-1);
	for (i = j = 0; s[i]; i++) {
		if (!Xisprint(s[i])) continue;
		if (ismsb(s[i])) return(-1);
		if (j >= strsize(str)) break;
		str[j++] = Xtolower(s[i]);
	}
	if (!j) return(-1);
	str[j] = '\0';
	len = j;

	if (!buf) chgroman(str, len, NULL);
	else {
#ifdef	DEP_FILECONV
		buf = kanjiconv2(tmp, buf,
			strsize(tmp), defaultkcode, DEFCODE, L_FNAME);
#endif
		memset((char *)kbuf, 0, sizeof(kbuf));
		if (!str2jis(kbuf, arraysize(kbuf), buf)) return(-1);
		chgroman(str, len, kbuf);
	}
	qsort(romanlist, maxromanlist, sizeof(romantable), cmproman);

	return(0);
}
