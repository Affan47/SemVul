acdSetScop(AcdPAcd thys)
{
    AjPFile val;

    AjPStr name     = NULL;
    AjBool required = ajFalse;
    AjBool ok       = ajFalse;

    ajint itry;
    AjPStr fmt    = NULL;

    val = NULL;

    acdAttrResolve(thys, "name", &name);

    if (!acdGetValueAssoc(thys, "format", &fmt))
	ajStrAssignClear(&fmt);

    required = acdIsRequired(thys);
    acdReplyInitS(thys, name, &acdReplyDef);
    acdPromptScop(thys);

    for(itry=acdPromptTry; itry && !ok; itry--)
    {
	ok = ajTrue;

	ajStrAssignS(&acdReply, acdReplyDef);

	if(required)
	    acdUserGet(thys, &acdReply);

	if(ajStrGetLen(acdReply))
	{
	    val = ajFileNewInNameS(acdReply);

	    if(!val)
	    {
		acdBadVal(thys, required,
			  "Unable to read scop data '%S'", acdReply);
		ok = ajFalse;
	    }
	}
	else
	{
	    acdBadVal(thys, required, "Scop data file is required");
	    ok = ajFalse;
	}
    }

    if(!ok)
	acdBadRetry(thys);

    thys->Value = val;
    ajStrAssignS(&thys->ValStr, acdReply);

    ajStrDel(&name);
    ajStrDel(&fmt);

    return;
}
