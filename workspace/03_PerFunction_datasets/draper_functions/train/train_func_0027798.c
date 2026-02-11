ajRegExec(AjPRegexp prog, const AjPStr str)
{
    int startoffset = 0;
    int options     = 0;
    int status      = 0;

    status = pcre_exec(prog->pcre, prog->extra, ajStrGetPtr(str),
                       ajStrGetLen(str), startoffset, options, prog->ovector,
                       3*prog->ovecsize);

    if(status >= 0)
    {
	prog->orig = ajStrGetPtr(str);

	if(status == 0)
	    ajWarn("ajRegExec too many substrings");

	return ajTrue;
    }

    if(status < -1)
    {
	ajDebug("ajRegExec returned unexpected status '%d'\n", status);
	prog->orig = ajStrGetPtr(str);
	ajRegTrace(prog);
    }

    prog->orig = NULL;

    return ajFalse;
}
