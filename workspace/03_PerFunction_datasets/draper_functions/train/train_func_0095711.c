makedest(str,start,ssize,size)

char *str;
int start, ssize, size;
{
    char *fr = dst;
    char *to = str;
    int as, asize, c;

    while (*fr && size >= 0) {
	if (*fr == AMPERSAND) {
	    if ((size -= ssize) < 0)
		return -1;
	    moveleft(&core[start],to,ssize);
	    to += ssize;
	    fr++;
	}
	else if (*fr == ESCAPE) {
	    c = fr[1];
	    fr += 2;
	    if (c >= '1' && c <= '9') {
		if ((as = RE_start[c-'1']) < 0)
		    continue;
		asize = RE_size [c-'1'];
		if ((size -= asize) < 0)
		    return -1;
		moveleft(&core[as],to,asize);
		to += asize;
	    }
	    else
		*to++ = c;
	}
	else {
	    *to++ = *fr++;
	    --size;
	}
    }
    return to-str;
}
