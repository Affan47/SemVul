featTagSpecialAllDbxref(const AjPStr val)
{
    const char* cp = NULL;
    AjBool ret           = ajTrue;


    cp = ajStrGetPtr(val);


    while(*cp && (*cp != ':'))
    {


	cp++;
    }

    if(!*cp)
	ret = ajFalse;
    else
    {
	cp++;
	if(!*cp)
	    ret = ajFalse;
    }


    if(!ret)
    {
	ajFeatWarn("bad /db_xref value '%S'",   val);
    }

    return ret;
}
