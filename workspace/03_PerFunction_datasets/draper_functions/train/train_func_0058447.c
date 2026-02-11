xmlinQueryMatch(const AjPQuery thys, const AjPXml xml)
{
    AjBool tested = ajFalse;
    AjIList iterfield  = NULL;
    AjPQueryField field = NULL;
    AjBool ok = ajFalse;

    ajDebug("xmlinQueryMatch '%S' fields: %u Case %B Done %B\n",
	    xml->Id, ajListGetLength(thys->QueryFields),
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
            ajDebug("  id test: '%S'\n",
                    xml->Id);
            if(thys->CaseId)
            {
                if(ajStrMatchWildS(xml->Id, field->Wildquery))
                {
                    ajListIterDel(&iterfield);
                    return ajTrue;
                }
            }
            else
            {
                if(ajStrMatchWildCaseS(xml->Id, field->Wildquery))
                {
                    ajListIterDel(&iterfield);
                    return ajTrue;
                }
            }

            ajDebug("id test failed\n");
            tested = ajTrue;
            ok = ajFalse;
        }

        if(ajStrMatchC(field->Field, "acc"))
        {
            if(ajStrMatchWildCaseS(xml->Id, field->Wildquery))
            {
                ajListIterDel(&iterfield);
                return ajTrue;
            }
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
