BDecTag PARAMS( (b, bytesDecoded, env),
BUF_TYPE  b _AND_
AsnLen* bytesDecoded _AND_
jmp_buf env)
{
    AsnTag tagId;
    AsnTag tmpTagId;
    int i;

    tagId = ((AsnTag)BufGetByte(b)) << ((sizeof(AsnTag)-1)*8);
    (*bytesDecoded)++;


    if ( (tagId & (((AsnTag) 0x1f) << ((sizeof(AsnTag)-1)*8))) ==
          (((AsnTag)0x1f) << ((sizeof(AsnTag)-1)*8)))
    {
        i = 2;
        do
        {
            tmpTagId = (AsnTag) BufGetByte(b);
            tagId |= (tmpTagId << ((sizeof(AsnTag)-i)*8));
            (*bytesDecoded)++;
            i++;
        }
        while ((tmpTagId & (AsnTag)0x80) && (i < sizeof(AsnTag)));


        if (i > (sizeof(AsnTag)+1))
        {
            Asn1Error("BDecTag: ERROR - tag value overflow\n");
            longjmp(env, -25);
        }
    }

    if (BufReadError(b))
    {
        Asn1Error("BDecTag: ERROR - decoded past the end of data\n");
        longjmp(env, -26);
    }

    return(tagId);

}
