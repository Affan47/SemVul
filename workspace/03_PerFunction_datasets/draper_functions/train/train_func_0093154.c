jis2ujis(buffer)
     unsigned char *buffer;
{
    unsigned char *p, *q;
    int kanji=0;

    p = q = buffer;
    while(*p != '\0') {
	if (*p == '\033') {
	    if ((p[1] == '$') &&
		((p[2] == '@') || (p[2] == 'B'))) {
		kanji = 1;
		p += 2;
	    } else if ((p[1] == '(') &&
		       ((p[2] == 'B') || (p[2] == 'J'))) {
		kanji = 0;
		p += 2;
	    } else {
		*(q ++) = *p;
	    }
	} else {
	    if (kanji) {
		*(q ++) = *(p ++) | 0x80;
		*(q ++) = *p | 0x80;
	    } else {
		*(q ++) = *p;
	    }
	}
	++ p;
    }
    *q = '\0';
}
