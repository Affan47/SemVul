getp(int obj,int prop)
{
    int p;

    for (; obj; obj = getofield(obj,O_CLASS))
	if (p = findprop(obj,prop))
	    return (getofield(obj,p));
    return (NIL);
}
