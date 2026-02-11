jis2defcode(c)
u_int c;
{
#ifndef	CODEEUC
	CONST char *cp;
	char buf[MAXKLEN + 1], tmp[MAXKLEN + 1];
#endif

	if (!(c & ~0xff)) {
#ifdef	CODEEUC
		if (Xiskana(c)) c |= (C_EKANA << 8);
#endif
		return(c);
	}

#ifdef	CODEEUC
	return(c | 0x8080);
#else
	VOID_C code2kanji(tmp, c | 0x8080);
	cp = kanjiconv2(buf, tmp, MAXKLEN, EUC, DEFCODE, L_INPUT);
	if (kanjierrno) return(0);

	return(((u_char)(cp[0]) << 8) | (u_char)(cp[1]));
#endif
}
