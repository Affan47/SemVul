ajHttpRedirect(AjPFilebuff buff, AjPStr* host, ajint* port, AjPStr* path,
                      ajuint *httpcode)
{

    AjPRegexp httpexp  = NULL;
    AjPRegexp nullexp  = NULL;
    AjPRegexp redirexp = NULL;

    AjPStr codestr  = NULL;
    AjPStr newurl   = NULL;
    AjPStr newhost  = NULL;
    AjPStr currline = NULL;

    AjBool isheader = ajFalse;
    AjBool ret = ajFalse;

    httpexp  = ajRegCompC("^HTTP/\\S+\\s+(\\d+)");

    if(!buff->Size)
	return 0;

    ajBuffreadLine(buff, &currline);

    ajDebug("ajHttpRedirect: First line: '%S'\n", currline);

    if(ajRegExec(httpexp, currline))
    {
        isheader = ajTrue;
        ajRegSubI(httpexp, 1, &codestr);
        ajStrToUint(codestr, httpcode);
        ajDebug("Header: codestr '%S' code '%u'\n", codestr, *httpcode);
        ajStrDel(&codestr);
    }

    if(isheader)
    {
        if(*httpcode == 301 || *httpcode == 302 || *httpcode==307)
        {
            redirexp = ajRegCompC("^Location: (\\S+)");
            nullexp  = ajRegCompC("^\r?\n?$");

            while( ajBuffreadLine(buff, &currline) &&
                  !ajRegExec(nullexp, currline))
            {
        	ajDebug("ajHttpRedirect: header line: '%S'\n", currline);

        	if(ajRegExec(redirexp, currline))
                {
                    ajRegSubI(redirexp, 1, &newurl);
                    ajHttpUrlDeconstruct(newurl, port, &newhost, path);

                    if(ajStrGetLen(newhost))
                	ajStrAssignS(host, newhost);

                    ajStrDel(&newurl);
                    ajStrDel(&newhost);
                    ret = ajTrue;
                    break;
                }
            }

            ajRegFree(&redirexp);
            ajRegFree(&nullexp);
        }
    }

    if(!ret)
	ajFilebuffReset(buff);

    ajRegFree(&httpexp);
    ajStrDel(&currline);

    return ret;
}
