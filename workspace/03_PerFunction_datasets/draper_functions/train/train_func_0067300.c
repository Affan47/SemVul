acdAttrTestDefined(const AcdPAcd thys,const  char *attrib)
{
    AcdPAttr attr;
    AjPStr  *attrstr;
    AcdPAttr defattr = acdAttrDef;
    AjPStr  *defstr;
    ajint i;

    attrstr = thys->AttrStr;
    defstr = thys->DefStr;


    if(acdIsQtype(thys))
	attr = acdType[thys->Type].Attr;
    else
	attr = acdKeywords[thys->Type].Attr;

    i = acdFindAttrC(attr, attrib);

    if(i >= 0)
    {
	if (ajStrGetLen(attrstr[i]))
	    return ajTrue;
	else
	    return ajFalse;
    }


    if(thys->DefStr)
    {
	i = acdFindAttrC(defattr, attrib);

	if(i >= 0)
	{
	    if (ajStrGetLen(defstr[i]))
		return ajTrue;
	    else
		return ajFalse;
	}
    }

    return ajFalse;
}
