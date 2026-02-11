ajStrCutRange(AjPStr* Pstr, ajlong pos1, ajlong pos2)
{
    AjPStr thys;
    size_t ilen;
    size_t ibegin;
    size_t iend;
    size_t irest;

    if(!*Pstr)
        *Pstr = ajStrNewResLenC("", 1, 0);
    else if((*Pstr)->Use > 1)
        ajStrGetuniqueStr(Pstr);

    thys = *Pstr;

    ibegin = ajCvtSposToPosStart(thys->Len, 0, pos1);
    iend   = ajCvtSposToPosStart(thys->Len, ibegin, pos2) + 1;
    ilen = iend - ibegin;


    irest = thys->Len - iend + 1;

    if(irest > 0)
      memmove(&thys->Ptr[ibegin], &thys->Ptr[iend], irest);

    thys->Len -= ilen;
    thys->Ptr[thys->Len] = '\0';

    return ajTrue;
}
