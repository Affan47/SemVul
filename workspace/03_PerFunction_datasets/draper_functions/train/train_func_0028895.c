ajUserGet(AjPStr* pthis, const char* fmt, ...)
{
    AjPStr thys;
    const char *cp;
    char *buff;
    va_list args;
    ajint ipos;
    ajint isize;
    ajint ilen;
    ajint jlen;
    ajint fileBuffSize = ajFileValueBuffsize();

    va_start(args, fmt);
    ajFmtVError(fmt, args);
    va_end(args);

    if(ajFileValueRedirectStdin())
    {
	ajUser("(Standard input in use: using default)");
	ajStrAssignC(pthis, "");

	return ajStrGetLen(*pthis);
    }

    ajStrSetRes(pthis, fileBuffSize);
    buff  = ajStrGetuniquePtr(pthis);
    thys = *pthis;
    isize = ajStrGetRes(thys);
    ilen  = 0;
    ipos  = 0;


    while(buff)
    {

#ifndef __ppc__
	cp = fgets(&buff[ipos], isize, stdin);
#else
	cp = ajSysFuncFgets(&buff[ipos], isize, stdin);
#endif

        if(!cp && !ipos)
	{
	    if(feof(stdin))
	    {
		ajErr("Unable to get reply from user - end of standard input");
		ajExitBad();
	    }
	    else
		ajFatal("Error reading from user: '%s'\n",
			strerror(errno));
	}

	jlen = strlen(&buff[ipos]);
	ilen += jlen;


	ajStrSetValidLen(pthis, ilen);
	thys = *pthis;

	if((jlen == (isize-1)) &&
	   (ajStrGetCharLast(thys) != '\n'))
	{
	    ajStrSetRes(pthis, ajStrGetRes(thys)+fileBuffSize);
	    thys = *pthis;


	    ipos += jlen;
	    buff = ajStrGetuniquePtr(pthis);
	    isize = ajStrGetRes(thys) - ipos;


	}
	else
	    buff = NULL;
    }

    ajStrSetValidLen(pthis, ilen);

    if(ajStrGetCharLast(*pthis) == '\n')
	ajStrCutEnd(pthis, 1);


    if(ajStrGetCharLast(*pthis) == '\r')
    {

	ajStrCutEnd(pthis, 1);
    }

    ajStrTrimWhite(pthis);

    return ajStrGetLen(*pthis);
}
