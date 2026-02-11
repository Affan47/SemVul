ajStrFmtPercentEncodeC(AjPStr* Pstr, const char* txt)
{
    AjPStr thys;
    AjPStr copy;

    char *cp;
    char *cq;
    int ia;
    int ip;
    int iq;
    size_t ir;
    ajuint i;
    ajuint npct;

    AjBool changed = ajFalse;

    if(!*Pstr)
        *Pstr = ajStrNewResLenC("", 1, 0);
    else if((*Pstr)->Use > 1)
        ajStrGetuniqueStr(Pstr);

    thys = *Pstr;
    npct = (ajuint) ajStrCalcCountC(thys, txt);
    if(!npct)
        return ajTrue;

    copy = ajStrNewS(thys);
    ajStrSetRes(Pstr, thys->Len + 3*npct);
    thys = *Pstr;

    cp = copy->Ptr;
    cq = thys->Ptr;

    while(*cp)
    {
        ir = strcspn(cp, txt);

        for(i=0; i < ir; i++)
            *cq++ = *cp++;

        if(*cp)
        {
            changed = ajTrue;
            ia = (int) *cp;
            ip = ia / 16;
            iq = ia % 16;

            *cq++ = '%';

            if(ip < 10)
                *cq++ = '0' + ip;
            else
                *cq++ = 'A' - 10 + ip;

            if(iq < 10)
                *cq++ = '0' + iq;
            else
                *cq++ = 'A' - 10 + iq;

            cp++;
        }
    }

    *cq = '\0';
    thys->Len = cq - thys->Ptr;

    if(changed)
        ajDebug("ajStrFmtPercentEncodeC changed '%s' '%S' => '%S'\n",
                txt, copy, thys);

    ajStrDel(&copy);

    return ajTrue;
}
