assemQueryMatch(const AjPQuery thys, const AjPAssem assem)
{
    AjBool tested = ajFalse;
    AjIList iterfield  = NULL;
    AjIList iter       = NULL;
    AjPQueryField field = NULL;
    AjBool ok = ajFalse;
    const AjPAssemContig c = NULL;

    ajDebug("assemQueryMatch '%S' fields: %Lu Case %B Done %B\n",
	    assem->Id, ajListGetLength(thys->QueryFields),
            thys->CaseId, thys->QryDone);

    if(!thys)
	return ajTrue;

    if(thys->QryDone)
	return ajTrue;


    iterfield = ajListIterNewread(thys->QueryFields);
    while(!ajListIterDone(iterfield))
    {
        field = ajListIterGet(iterfield);

        ajDebug("  field: '%S' Query: '%S'\n",
                field->Field, field->Wildquery);
        if(ajStrMatchC(field->Field, "id"))
        {
            ajDebug("  id test: %Lu\n",
                    ajListGetLength(assem->ContigsOrder));

            iter = ajListIterNewread(assem->ContigsOrder);
            while(!ajListIterDone(iter))
            {
                c = ajListIterGet(iter);

                ajDebug("test case %B '%S'\n", thys->CaseId, c->Name);
                if(thys->CaseId)
                {
                    if(ajStrMatchWildS(c->Name, field->Wildquery))
                    {
                        ajListIterDel(&iterfield);
                        ajListIterDel(&iter);
                        return ajTrue;
                    }
                }
                else
                {
                    if(ajStrMatchWildCaseS(c->Name, field->Wildquery))
                    {
                        ajListIterDel(&iterfield);
                        ajListIterDel(&iter);
                        return ajTrue;
                    }
                }
            }
            ajListIterDel(&iter);

            tested = ajTrue;
        }

    }

    ajListIterDel(&iterfield);

    if(!tested)
    {
        ajDebug("  no tests: assume OK\n");
	return ajTrue;
    }

    ajDebug("result: %B\n", ok);

    return ok;
}
