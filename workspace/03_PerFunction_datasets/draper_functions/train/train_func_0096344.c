getlang(s, io)
CONST char *s;
int io;
{
	int i, ret;

	ret = NOCNV;
	if (s) for (i = 0; i < LANGLISTSIZ; i++) {
		if (!(kanjiiomode[langlist[i].lang] & io)) continue;
		if (Xstrstr(s, langlist[i].ident)) {
			ret = langlist[i].lang;
			break;
		}
	}

# ifndef	_NOKANJICONV
	if (io == L_INPUT && ret == NOCNV) ret = DEFCODE;
# endif

	return(ret);
}
