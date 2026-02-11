output(fp, c, mode)
FILE *fp;
int c, mode;
{
	static u_char buf[2];
	static int kanji1 = 0;
	static int bufp = 0;

	if (!fp) {
		bufp = kanji1 = 0;
		return;
	}

	if (!bufp) ;
	else if (bufp > 1) {
		convert(buf[0], buf[1], fp);
		bufp = 0;
	}
	else if (kanji1 & (KANA | JKANA)) {
		convert(0, buf[0], fp);
		bufp = 0;
	}
	else if (!(kanji1 & KANJI)) {
		Xfputc(buf[0], fp);
		bufp = 0;
	}
	kanji1 = mode;

	if (c != EOF) buf[bufp++] = c;
}
