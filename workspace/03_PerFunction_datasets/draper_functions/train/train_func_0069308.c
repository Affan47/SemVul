decodeSize(XMLCSTR data,XMLError *xe)
{
     if (xe) *xe=eXMLErrorNone;
    int size=0;
    unsigned char c;

    while (*data)
    {
#ifdef _XMLWIDECHAR
        if (*data>255) { if (xe) *xe=eXMLErrorBase64DecodeIllegalCharacter; return 0; }
#endif
        c=base64DecodeTable[(unsigned char)(*data)];
        if (c<97) size++;
        else if (c==98) { if (xe) *xe=eXMLErrorBase64DecodeIllegalCharacter; return 0; }
        data++;
    }
    if (xe&&(size%4!=0)) *xe=eXMLErrorBase64DataSizeIsNotMultipleOf4;
    if (size==0) return 0;
    do { data--; size--; } while(*data==base64Fillchar); size++;
    return (unsigned int)((size*3)/4);
}
