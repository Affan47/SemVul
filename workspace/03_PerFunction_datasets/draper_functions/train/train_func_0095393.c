chainprefix(pretype, sufftype)
struct typestruct *pretype;
struct typestruct *sufftype;
{
    if (pretype->nexttype != NULL)
    {
	sufftype = chainprefix(pretype->nexttype, sufftype);
	if (pretype->constructor != ARRAY)
	    return prefix(pretype->constructor, pretype->typesize, sufftype);
	else
	    return prefix(ARRAY,
			  pretype->typesize / pretype->nexttype->typesize
					    * sufftype->typesize, sufftype);
    }
    return sufftype;
}
