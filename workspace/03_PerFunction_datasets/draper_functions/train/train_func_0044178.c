pproceof()
{
    if (infiln != 0)
	close(infil);
    if (infiln == infil0)

    {
	if (blocklevel != 0)
	    error(EOFBLOCK);
	if (iflevel != 0)
	    error(EOFIF);
	if (pass && (lcdata & UNDBIT))
	    error(EOFLC);
	lcptr->data = lcdata;
	lcptr->lc = lc;
    }

    if (macload)
	error(EOFMAC);
    if (linebuf != lineptr)
        listline();
    if (infiln != infil0)
    {
	--getstak;
	infil = getstak->fd;
	linum = getstak->line;
	if (--infiln == 0)
	    eol_ptr = (void*)getstak->position;
	else
#if MINIBUF == 1
	    inp_seek(infil, getstak->position);
#else
	    lseek(infil, getstak->position, 0);
#endif
    }
    else if (pass!=last_pass)
    {
	pass++;
	if( last_pass>1 && last_pass<30 && dirty_pass && pass==last_pass )
	   last_pass++;

	if( pass==last_pass )
	   objheader();
	binmbuf = 0;
	maclevel = iflevel = blocklevel =
	    totwarn = toterr = linum = macnum = 0;
	initp1p2();
	if(pass==last_pass)
	   binaryc = binaryg;
#ifdef I80386
	defsize = idefsize;
	cpuid = origcpuid;
#endif
	if(pass==last_pass)
	{
	   list.current = list.global;
	   maclist.current = maclist.global;
	   as_warn.current = TRUE;
	   if (as_warn.semaphore < 0)
	       as_warn.current = FALSE;
	}

	if (infiln != 0)
	    infil = open_input(filnamptr);
        else
	    eol_ptr=0;

	if(pass==last_pass)
	   binheader();

	line_zero();
    }
    else
	finishup();
}
