Perl_mem_collxfrm(pTHX_ const char *s, STRLEN len, STRLEN *xlen)
{
    dVAR;
    char *xbuf;
    STRLEN xAlloc, xin, xout;

    PERL_ARGS_ASSERT_MEM_COLLXFRM;


    xAlloc = sizeof(PL_collation_ix) + PL_collxfrm_base + (PL_collxfrm_mult * len) + 1;
    Newx(xbuf, xAlloc, char);
    if (! xbuf)
	goto bad;

    *(U32*)xbuf = PL_collation_ix;
    xout = sizeof(PL_collation_ix);
    for (xin = 0; xin < len; ) {
	Size_t xused;

	for (;;) {
	    xused = strxfrm(xbuf + xout, s + xin, xAlloc - xout);
	    if (xused >= PERL_INT_MAX)
		goto bad;
	    if ((STRLEN)xused < xAlloc - xout)
		break;
	    xAlloc = (2 * xAlloc) + 1;
	    Renew(xbuf, xAlloc, char);
	    if (! xbuf)
		goto bad;
	}

	xin += strlen(s + xin) + 1;
	xout += xused;


    }

    xbuf[xout] = '\0';
    *xlen = xout - sizeof(PL_collation_ix);
    return xbuf;

  bad:
    Safefree(xbuf);
    *xlen = 0;
    return NULL;
}
