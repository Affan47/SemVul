ajStrMaskRange(AjPStr* Pstr, ajlong pos1, ajlong pos2, char maskchr)
{
    AjPStr thys;
    size_t ibegin;
    size_t iend;
    size_t i;

    if(!*Pstr)
        *Pstr = ajStrNewResLenC("", 1, 0);
    else if((*Pstr)->Use > 1)
        ajStrGetuniqueStr(Pstr);

    thys = *Pstr;

    ibegin = ajCvtSposToPosStart(thys->Len, 0, pos1);
    iend = ajCvtSposToPosStart(thys->Len, ibegin, pos2);


    if(iend < ibegin)
	return ajFalse;

    for(i=ibegin; i<=iend; i++)
	thys->Ptr[i] = maskchr;

    return ajTrue;
}
