plD_eop_ljiip(PLStream *pls)
{
    PLINT j;
    unsigned char _HUGE *p;
    int iw;
#if GCMODE > 0
    int i, iy, last, n, jmax;
    unsigned char _HUGE t_buf[BPROW*2];
    unsigned char c;
#endif


    fprintf(OF,"\033*rB");
    fprintf(OF,"\033*t%3dR", DPI);

#if GCMODE != 0
    fprintf(OF,"\033*r%dS", XDOTS);
    fprintf(OF,"\033*b%1dM", GCMODE);
#endif


    fprintf(OF,"\033*p%ldX", CURX);
    fprintf(OF,"\033*p%ldY", CURY);
    fprintf(OF,"\033*r0A");


#if GCMODE == 0
    for (j = 0, p = bitmap; j < YDOTS; j++, p += BPROW1) {
	fprintf(OF,"\033*b>%dW", BPROW);
	iw = fwrite(p, BPROW, sizeof(char), OF);
    }
#endif
#if GCMODE == 2
    for (iy = 0, p = bitmap; iy < YDOTS; iy++, p += BPROW1) {


	last = BPROW - 1;
	while (last > 0 && p[last] == 0) last--;
	last++;


	i = n = 0;
	while (i < last) {
	    c = p[i];
	    jmax = i + 127;
	    jmax = last < jmax ? last : jmax;
	    if (i < last - 2 && (c == p[i+1]) && (c == p[i+2])) {
		j = i + 3;
		while (j < jmax && c == p[j]) j++;
		t_buf[n++] = (i-j+1) & 0xff;
		t_buf[n++] = c;
		i = j;
	    }
	    else {
		for (j = i + 1; j < jmax; j++) {
		    if (j < last - 2 && (p[j] == p[j+1]) &&
			(p[j+1] == p[j+2]) ) break;
		}
		t_buf[n++] = j - i - 1;
		while (i < j) {
		    t_buf[n++] = p[i++];
		}
	    }
	}
	fprintf(OF,"\033*b%dW", (int) n);
	iw = fwrite(t_buf, (int) n, sizeof(char), OF);
    }
#endif

    pls->bytecnt += NBYTES;


    fprintf(OF, "\033*rB");
    fprintf(OF, "%c", FF);


    memset((void *) bitmap, '\0', NBYTES);
}
