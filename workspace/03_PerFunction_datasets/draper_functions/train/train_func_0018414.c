linkytitle(MMIOT *f, char quote, Footnote *ref)
{
    int whence = mmiottell(f);
    char *title = cursor(f);
    char *e;
    register int c;

    while ( (c = pull(f)) != EOF ) {
	e = cursor(f);
	if ( c == quote ) {
	    if ( (c = eatspace(f)) == ')' ) {
		T(ref->title) = 1+title;
		S(ref->title) = (e-title)-2;
		return 1;
	    }
	}
    }
    mmiotseek(f, whence);
    return 0;
}
