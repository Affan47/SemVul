featEmblFromLine(AjPFeattable thys,
				   const AjPStr origline,
				   AjPStr* savefeat,
				   AjPStr* saveloc,
				   AjPStr* saveline)
{
    static AjPFeature gf = NULL;
    AjPStr temp   = NULL;
    AjBool newft         = ajFalse;
    AjBool doft         = ajFalse;

    if(!featinSourceEmbl)
	featinSourceEmbl = ajStrNewC("EMBL");

    if(origline)
    {

	ajStrAssignS(&featProcessLine,origline);

	ajStrCutStart(&featProcessLine, 5);


        if(ajStrGetCharFirst(featProcessLine) != ' ')
	{
	    newft = ajTrue;

	    if(ajStrGetLen(*saveloc))
		doft = ajTrue;
	}
    }
    else
    {
	ajStrAssignClear(&featProcessLine);
	newft = ajFalse;

	if(ajStrGetLen(*saveloc))
	    doft = ajTrue;
    }


    if(doft)
    {


	gf = featEmblProcess(thys, *savefeat, featinSourceEmbl,
			     saveloc, saveline);

	ajStrDelStatic(saveloc);
	ajStrDelStatic(saveline);
    }

    if(!origline)
    {
	if(doft)
            return gf;
        else
            return NULL;
    }

    ajStrRemoveWhiteExcess(&featProcessLine);

    if(newft)
    {
	ajStrTokenAssignC(&featEmblSplit, featProcessLine, " ");
	ajStrTokenNextParse(featEmblSplit, savefeat);

	if(ajStrTokenNextParseC(featEmblSplit, " /", saveloc))
	    ajStrTokenRestParse(featEmblSplit, saveline);
	else
	    ajStrAssignResC(saveline, 512, "");

	ajStrTokenDel(&featEmblSplit);

	return gf;
    }
    else if(!ajStrGetLen(*saveline))
    {
	if(ajStrGetCharFirst(featProcessLine) != '/')
	{
	    ajStrTokenAssignC(&featEmblSplit, featProcessLine, " ");
	    ajStrTokenNextParse(featEmblSplit, &temp);

	    if(ajStrGetLen(temp))
		ajStrAppendS(saveloc, temp);

	    ajStrTokenRestParse(featEmblSplit, &temp);

	    if(ajStrGetLen(temp))
		ajStrAppendS(saveline, temp);

	    ajStrDel(&temp);
	    ajStrTokenDel(&featEmblSplit);

	    return gf;
	}
    }


    ajStrAppendK(saveline, ' ');
    ajStrAppendS(saveline, featProcessLine);

    return gf;
}
