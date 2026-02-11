acdSetDistances(AcdPAcd thys)
{
    AjPPhyloDist* val = NULL;

    AjBool required = ajFalse;
    AjBool ok       = ajFalse;

    AjPStr infname  = NULL;
    ajint itry;

    AjBool nullok = ajFalse;
    ajint size;
    AjBool missing;
    ajint i;

    val = NULL;

    acdAttrToBool(thys, "nullok", ajFalse, &nullok);
    acdAttrToInt(thys, "size", 0, &size);
    acdAttrToBool(thys, "missval", ajFalse, &missing);

    acdInFilename(&infname);
    required = acdIsRequired(thys);
    acdReplyInitS(thys, infname, &acdReplyDef);
    acdPromptInfile(thys);
    ajStrDel(&infname);

    for(itry=acdPromptTry; itry && !ok; itry--)
    {
	ok = ajTrue;

	ajStrAssignS(&acdReply, acdReplyDef);

	if(required)
	    acdUserGet(thys, &acdReply);

	if(ajStrGetLen(acdReply))
	{
	    val = ajPhyloDistRead(acdReply, size, missing);

	    if(!val)
	    {
		acdBadVal(thys, required,
			  "Unable to read distances file '%S'",
			  acdReply);
		ok = ajFalse;
	    }
	}
	else
	    if(!nullok)
	    {
		acdBadVal(thys, required,
			  "Distances file is required");
		ok = ajFalse;
	    }
    }

    if(!ok)
	acdBadRetry(thys);

    acdInFileSave(acdReply, NULL, ajTrue);


    thys->SAttr = acdAttrListCount(acdCalcDistances);
    thys->SetAttr = &acdCalcDistances[0];
    thys->SetStr = AJCALLOC0(thys->SAttr, sizeof(AjPStr));

    if(val)
    {
	for(i=0;val[i];i++)
	    continue;
	ajStrFromInt(&thys->SetStr[0],i);
	ajStrFromInt(&thys->SetStr[1],val[0]->Size);
	ajStrFromBool(&thys->SetStr[2],val[0]->HasReplicates);
	ajStrFromBool(&thys->SetStr[3],val[0]->HasMissing);
 	ajStrAssignS(&thys->ValStr, acdReply);
    }
    else
    {
	ajStrFromInt(&thys->SetStr[0],0);
	ajStrFromInt(&thys->SetStr[1],0);
	ajStrFromBool(&thys->SetStr[2],ajFalse);
	ajStrFromBool(&thys->SetStr[3],ajFalse);
	ajStrAssignClear(&thys->ValStr);
    }

    thys->Value = val;

    return;
}
