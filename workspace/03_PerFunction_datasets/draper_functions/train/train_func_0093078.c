ajStrDelStatic(AjPStr* Pstr)
{
    AjPStr thys;

    if(!*Pstr)
	return ajFalse;

    thys = *Pstr;

    if(thys->Use == 1)
    {
	*thys->Ptr = '\0';
	thys->Len  = 0;
	return ajTrue;
    }
    else
    {
	--thys->Use;
	*Pstr = NULL;
    }

    return ajFalse;
}
