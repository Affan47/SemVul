DeEscapeString(const char *str)
{
    ASSERT(str);

    char *newstr = new char[STRLEN(str) + 1];
    char c, *pnew = newstr;
    const char *pstr = str;


    while ( (c = *pstr) ) {
	switch (c) {
	    case '\\':
		pstr++;
		switch (*pstr) {
		    case 'n': *pnew = '\n'; break;
		    case 't': *pnew = '\t'; break;
		    case 'r': *pnew = '\r'; break;
		    case 'f': *pnew = '\f'; break;
		    case 'b': *pnew = '\b'; break;
		    default:
			if (isdigit(*pstr)) {

			    int num = 0, i = 0;
			    pstr--;
			    do {
				pstr++;
				int digit = *pstr - '0';
				if (digit >= 8)
				    break;
				num = num*8 + *pstr - '0';
			    } while ((++i < 3) && isdigit(*(pstr+1)));
			    if (num > 0xff)
				    break;
			    *pnew = (char)num;
			} else {
			    *pnew = *pstr;
		    	}
		    }
		break;
	    default:
		*pnew = *pstr;
		break;
	}
	pnew++;
	pstr++;
    }
    *pnew = '\0';
    return newstr;
}
