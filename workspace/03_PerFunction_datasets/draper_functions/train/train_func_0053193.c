ajCharCmpWild(const char* txt, const char* txt2)
{
    const char* cp;
    const char* cq;


    cp = txt2;
    cq = txt;

    if(!*cp && !*cq)
	return 0;

    if(!*cp)
	return -1;


    while(*cp)
    {
	if(!*cq && *cp != '*')
	    return 1;

	switch(*cp)
	{
	case '?':
	    cp++;
	    cq++;
	    break;
	case '*':
	    cp++;

	    if(!*cp)
	    {


		return 0;
	    }

	    if(!*cq)
	    {


		return ajCharCmpWild(cq, cp);
	    }

	    while(*cq)
	    {
		if(ajCharMatchWildC(cq, cp))
		    return 0;


		cq++;
	    }

	    return 1;


	default:
	    if(*cp != *cq)
	    {
		if(*cp > *cq)
		    return -1;
		else
		    return 1;
	    }

	    cp++;

	    if(*cq)
		cq++;
	}
    }


    if(*cp)
    {

	return -1 ;
    }

    if(*cq)
    {

	return 1;
    }


    return 0;
}
