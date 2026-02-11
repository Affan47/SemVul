PUTStr_aux(next,chLeft,c,s)
String next;
Int*   chLeft;
Char   c;
String s; {
    Int charsLeft = *chLeft;
    Int len;
    if (s && (len = strlen(s)) > 0 ) {
	String t = 0;
	len = strlen(s);

	if ( (Int)(len + 10) > charsLeft ) {
	    *next = '\0';


	    return next;
	}

	*next++ = '-';
	*next++=c;
	*next++='"';
	charsLeft -= 3;


	*next = '\0';
	for(t=s; *t; ) {


	    String strChar = unlexChar(ExtractChar(t),'"');
	    PUTS(strChar);
	}
	next+=strlen(next);
	PUTS("\" ");
    }
    *chLeft = charsLeft;
    return next;
}
