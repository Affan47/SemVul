ajStrDel(AjPStr* Pstr)
{
    AjPStr thys;

    if(!Pstr)
	return;

    if(!*Pstr)
	return;

    thys = *Pstr;

    if(!thys->Use)
        ajErr("trying to delete unused string");

    --thys->Use;

    if(!thys->Use)
    {
	if(thys == strPNULL)
	{
	    ajErr("Error - trying to delete the null string constant\n");
	    thys->Use = NULL_USE;
	}
	else
	{
	    AJFREE(thys->Ptr);

#ifdef AJ_SAVESTATS
	    strFree += thys->Res;
	    strFreeCount++;
	    strCount--;
#endif

	    thys->Res = 0;
	    thys->Len = 0;

	    AJFREE(*Pstr);
	}
    }

    *Pstr = NULL;

    return;
}
