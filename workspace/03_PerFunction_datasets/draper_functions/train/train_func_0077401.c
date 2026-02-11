acdAttrToUint(const AcdPAcd thys,
			   const char *attr, ajuint defval, ajuint *result)
{
    acdAttrResolve(thys, attr, &acdAttrValTmp);

    if(ajStrGetLen(acdAttrValTmp))
    {
	if(ajStrToUint(acdAttrValTmp, result))
	{
	    ajStrDelStatic(&acdAttrValTmp);

	    return ajTrue;
	}
	else
	    acdErrorAcd(thys, "Bad attribute unsigned integer value %s = %S\n",
			attr, acdAttrValTmp);
    }

    *result = defval;
    ajStrDelStatic(&acdAttrValTmp);

    return ajFalse;
}
