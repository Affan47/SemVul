readHexChar() {
    Int n = 0;
    Int d;

    skip();
    if ((d = readHexDigit(c0))<0) {
	ERRMSG(row) "Empty hexadecimal character escape"
	EEND;
    }
    do {
	if (overflows(n,16,d,MAXCHARVAL)) {
	    ERRMSG(row) "Hexadecimal character escape out of range"
	    EEND;
	}
	n = 16*n + d;
	skip();
    } while ((d = readHexDigit(c0))>=0);

    return mkChar(n);
}
