acdTestAssoc(const AcdPAcd thys, const AjPStr name,
			    const AjPStr noname)
{
    AcdPAcd pa;
    ajint ifound=0;
    AcdPAcd ret=NULL;
    AjPStr ambigList = NULL;

    ambigList = ajStrNew();

    for(pa=thys->AssocQuals; pa && pa->Assoc; pa=pa->Next)
	if(ajStrPrefixS(pa->Name, name) ||
	   ajStrPrefixS(pa->Name, noname))
	{
	    if(ajStrMatchS(pa->Name, name) ||
	       ajStrMatchS(pa->Name, noname))
	    {
		ajStrDel(&ambigList);
		return pa;
	    }
	    ifound++;
	    ret = pa;
	}

    if(ifound == 1)
    {
	if (acdDoValid)
	    acdWarn("Abbreviated associated qualifier '%S' (%S)",
		    name, ambigList);
	ajStrDel(&ambigList);
	return ret;
    }

    ajStrDel(&ambigList);

    return NULL;
}
