ajFeattablePosII(ajuint ilen, ajuint imin, ajint ipos)
{
    ajuint jpos;

    if(ipos < 0)
	jpos = ilen + ipos + 1;
    else
    {
	if(ipos)
	    jpos = ipos;
	else
	    jpos = 1;
    }

    if(jpos > ilen)
	jpos = ilen;

    if(jpos < imin)
	jpos = imin;


    return jpos;
}
