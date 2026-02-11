embBtreeEmblAC(const AjPStr acline, AjPList aclist)
{
    char *p          = NULL;
    char *q          = NULL;
    ajuint lo = 0;
    ajuint hi = 0;
    ajuint field = 0;
    ajuint i;
    AjPStr str = NULL;

    ajStrAssignSubS(&embindexLine, acline, 5, -1);

    ajStrTokenAssignC(&embindexHandle,embindexLine,"\n\r;");

    while(ajStrTokenNextParse(embindexHandle,&embindexToken))
    {
	ajStrTrimWhite(&embindexToken);

	if((p=strchr(MAJSTRGETPTR(embindexToken),(int)'-')))
	{
	    q = p;

	    while(isdigit((int)*(--q)));

	    ++q;
	    ajStrAssignSubC(&embindexTstr,q,0,(ajuint)(p-q-1));
	    ajStrToUint(embindexTstr,&lo);
	    field = (ajuint) (p-q);
	    ajFmtPrintS(&embindexFormat,"%%S%%0%uu",field);

	    ++p;
	    q = p;

	    while(!isdigit((int)*q))
		++q;

	    sscanf(q,"%u",&hi);
	    ajStrAssignSubC(&embindexPrefix,p,0,(ajuint)(q-p-1));

	    for(i=lo;i<=hi;++i)
	    {
		ajFmtPrintS(&str,MAJSTRGETPTR(embindexFormat),
			    embindexPrefix,i);
		ajListstrPush(aclist, str);
		str = NULL;
	    }
	}
	else
	{
	    ajStrAssignS(&str,embindexToken);
	    ajListstrPush(aclist, str);
	    str = NULL;
	}
    }

    return;
}
