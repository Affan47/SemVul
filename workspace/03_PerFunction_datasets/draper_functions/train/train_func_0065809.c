acdSetDirlist(AcdPAcd thys)
{
    AjPList val;
    AjPStr  t;
    AjPStr  v;
    AjBool required = ajFalse;
    AjBool ok       = ajFalse;

    ajint itry;

    AjBool nullok = ajFalse;
    AjBool dopath;
    AjPStr ext = NULL;
    ajint n;
    ajint i;

    val = NULL;

    acdAttrToBool(thys, "fullpath", ajFalse, &dopath);
    acdAttrToBool(thys, "nullok", ajFalse, &nullok);
    acdGetValueAssoc(thys, "extension", &ext);

    required = acdIsRequired(thys);
    acdReplyInitC(thys, ".", &acdReplyDef);
    acdPromptDirlist(thys);

    for(itry=acdPromptTry; itry && !ok; itry--)
    {
	ok = ajTrue;

	ajStrAssignS(&acdReply, acdReplyDef);

	if(required)
	    acdUserGet(thys, &acdReply);

        if(ajStrGetLen(acdReply))
	{
	    if(dopath)
		ok = ajDirnameFillPath(&acdReply);
	    else
		ok = ajDirnameFixExists(&acdReply);

	    if(!ok)
		acdBadVal(thys, required,
			  "Unable to open directories '%S' for input",
			  acdReply);
	}
	else
	    if(!nullok)
	    {
		acdBadVal(thys, required,
			  "Input file is required");
		ok = ajFalse;
	    }
    }

    if(!ok)
	acdBadRetry(thys);

    val = ajListstrNew();
    t   = ajStrNewC("*");

    if(MAJSTRGETLEN(ext))
    {
	if(ajStrGetCharFirst(ext) != '.')
	    ajStrInsertC(&ext, 0, ".");

	ajStrAppendS(&t, ext);
    }

    ajFilelistAddPathWild(val, acdReply, t);


    ajListSort(val, &ajStrVcmp);


    n = (ajuint) ajListGetLength(val);

    ajDebug("acdSetDirlist '%S' listlength %d\n",
	    acdReply, n);

    for(i=0;i<n;++i)
    {
	ajFmtPrintS(&t,"");
	ajListPop(val,(void **)&v);
	ajStrAppendS(&t,v);
	ajStrAssignS(&v,t);
	ajListPushAppend(val,(void *)v);
    }

    thys->Value = val;
    ajStrAssignS(&thys->ValStr, acdReply);

    ajStrDel(&t);
    ajStrDel(&ext);

    return;
}
