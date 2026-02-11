ujis2sjis(buf, s, max)
char *buf;
CONST u_char *s;
int max;
{
	int i, j;

	for (i = j = 0; s[i] && j < max; i++, j++) {
		if (isweuc((CONST char *)s, i)) {
			if (j + 2 > max) break;
			j2sj(&(buf[j++]), &(s[i++]));
		}
		else if (isekana(s, i)) buf[j] = s[++i];
		else buf[j] = s[i];
	}
	if (kanjierrno) kanjierrno = EUC;

	return(j);
}
