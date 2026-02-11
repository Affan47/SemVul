acdSetDirectory(AcdPAcd thys)
{
    AjPDir val;

    AjBool required = ajFalse;
    AjBool ok       = ajFalse;

    ajint itry;

    AjBool nullok = ajFalse;
    AjBool nulldefault = ajFalse;
    AjBool dopath = ajFalse;
    AjPStr ext = NULL;

    val = NULL;

    acdAttrToBool(thys, "fullpath", ajFalse, &dopath);
    acdAttrToBool(thys, "nullok", ajFalse, &nullok);
    acdAttrToBool(thys, "nulldefault", ajFalse, &nulldefault);
    acdGetValueAssoc(thys, "extension", &ext);

    required = acdIsRequired(thys);
    if(nullok && nulldefault)
    {
	if (acdDefinedEmpty(thys))
	    acdReplyInitC(thys, ".", &acdReplyDef);
	else
	    acdReplyInitC(thys, "", &acdReplyDef);
    }
    else
        acdReplyInitC(thys, ".", &acdReplyDef);

    acdPromptDirectory(thys);

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

	    if (ok)
	    {
		val = ajDirNewPathExt(acdReply, ext);
		if (!val)
		    ok = ajFalse;
	    }
	    if(!ok)
		acdBadVal(thys, required,
			  "Unable to open directory '%S'",
			  acdReply);
	}
	else
	    if(!nullok)
	    {
		acdBadVal(thys, required,
			  "Directory path is required");
		ok = ajFalse;
	    }
    }

    if(!ok)
	acdBadRetry(thys);

    thys->Value = val;
    ajStrAssignS(&thys->ValStr, acdReply);

    ajStrDel(&ext);

    return;
}
