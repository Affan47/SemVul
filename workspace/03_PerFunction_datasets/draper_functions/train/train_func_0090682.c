utf16toASCII(WORD *restrict source, char *restrict dest, int len) {
    int i;
    int res;
    wchar_t wc;

    if ( len > (NAME_MAX+1) ) len = NAME_MAX+1;

    for (i=0; i < len;) {

        res = unicode_utf16le_to_wchar(&wc, &(source[i]), 2);

        if (wc < 0x000080) {
    	    dest[i] = (char) wc;
		    if ( dest[i] == 0 ) {
				return 0;
   		    }
    	}  else {
	    	dest[i] = 0x5F;
		}
    	i++;


    	if (i == len) {
			dest[len]=0;
			return len;
    	} else {
    	    return i;
    	}
	}
	return 0;
}
