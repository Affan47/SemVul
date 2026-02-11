acdSetCodon(AcdPAcd thys)
{
    AjPCod val;

    AjPStr name     = NULL;
    AjBool required = ajFalse;
    AjBool ok       = ajFalse;

    ajint itry;
    AjBool nullok;
    AjPStr fmt    = NULL;

    val = ajCodNew();
    acdAttrResolve(thys, "name", &name);

    acdAttrToBool(thys, "nullok", ajFalse, &nullok);
    acdLog("nullok: %B\n", nullok);

    if (!acdGetValueAssoc(thys, "format", &fmt))
	ajStrAssignClear(&fmt);

    required = acdIsRequired(thys);
    acdReplyInitS(thys, name, &acdReplyDef);
    acdPromptCodon(thys);

    for(itry=acdPromptTry; itry && !ok; itry--)
    {
	ok = ajTrue;

	ajStrAssignS(&acdReply, acdReplyDef);

	if(required)
	    acdUserGet(thys, &acdReply);

	if(ajStrGetLen(acdReply))
	{
	    if(!ajCodRead(val, acdReply, fmt))
	    {
		acdBadVal(thys, required,
			  "Unable to read codon usage '%S'", acdReply);
		ok = ajFalse;
	    }
	}
	else
	{
	    if(nullok)
	    {
		ajCodDel(&val);
	    }
	    else
	    {
		acdBadVal(thys, required, "Codon file is required");
		ok = ajFalse;
	    }
	}
    }

    if(!ok)
	acdBadRetry(thys);

    acdInFileSave(acdReply, NULL, ajFalse);

    thys->Value = val;
    ajStrAssignS(&thys->ValStr, acdReply);

    ajStrDel(&name);
    ajStrDel(&fmt);

    return;
}
