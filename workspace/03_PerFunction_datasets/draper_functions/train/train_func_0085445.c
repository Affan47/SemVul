ajUtilBase64EncodeC(AjPStr *Pdest, size_t size, const unsigned char *src)
{
    size_t i;
    unsigned char b1 = 0;
    unsigned char b2 = 0;
    unsigned char b3 = 0;
    unsigned char b4 = 0;
    unsigned char b5 = 0;
    unsigned char b6 = 0;
    unsigned char b7 = 0;

    if(!src)
        return ajFalse;

    if(!Pdest)
        return ajFalse;

    if(!*Pdest)
        return ajFalse;

    if(!size)
        size = strlen((const char *)src);


    for(i = 0; i < size; i += 3)
    {
        b1 = src[i];

        if(i+1 < size)
            b2 = src[i+1];

        if(i+2 < size)
            b3 = src[i+2];

        b4 = b1 >> 2;
        b5 = ((b1 & 0x3) << 4) | (b2 >> 4);
        b6 = ((b2 & 0xf) << 2) | (b3 >> 6);
        b7 = b3 & 0x3f;

        ajStrAppendK(Pdest, utilBase64Encode(b4));
        ajStrAppendK(Pdest, utilBase64Encode(b5));

        if(i+1 < size)
            ajStrAppendK(Pdest, utilBase64Encode(b6));
        else
            ajStrAppendK(Pdest, '=');

        if(i+2 < size)
            ajStrAppendK(Pdest, utilBase64Encode(b7));
        else
            ajStrAppendK(Pdest, '=');
    }

    return ajTrue;
}
