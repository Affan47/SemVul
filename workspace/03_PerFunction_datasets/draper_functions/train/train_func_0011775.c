acdNewEndsec(const AjPStr name)
{
    AcdPAcd acd;
    static ajint firstcall = 1;
    static ajint ikey;
    AjPStr secname=NULL;

    if(firstcall)
    {
	ikey = acdFindKeyC("endsection");
	firstcall = 0;
    }

    acdLog("acdNewEndsec '%S' acdSecList length %d\n",
	   name, ajListstrGetLength(acdSecList));

    if(!ajListstrGetLength(acdSecList))
    {
	acdLog("Bad endsection '%S', not in a section\n", name);
	acdError("Bad endsection '%S', not in a section", name);
    }
    else
    {
	ajListstrPop(acdSecList, &secname);
	acdLog("Pop from acdSecList '%S' new length %d\n",
	       secname, ajListstrGetLength(acdSecList));

	if(!ajStrMatchS(name, secname))
	{
	    acdLog("Bad endsection '%S', current section is '%S\n'",
		   name, secname);
	    acdError("Bad endsection '%S', current section is '%S'",
		     name, secname);
	}
	ajStrDel(&secname);
    }

    acd = acdNewAcdKey(name, name, ikey);
    acd->Level = ACD_ENDSEC;

    return acd;
}
