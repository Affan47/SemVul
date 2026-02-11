ajStrGetuniqueStr(AjPStr* Pstr)
{
    AjPStr thys;

    if(!*Pstr)
    {
	*Pstr = ajStrNew();

	return *Pstr;
    }

    thys = *Pstr;

    if(thys->Use > 1)
	strClone(Pstr);

    return *Pstr;
}
