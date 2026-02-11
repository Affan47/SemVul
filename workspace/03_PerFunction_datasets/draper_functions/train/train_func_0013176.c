BDecAsnIntContent PARAMS((b, tagId, len, result, bytesDecoded, env),
BUF_TYPE   b _AND_
AsnTag     tagId _AND_
AsnLen     len _AND_
AsnInt*    result _AND_
AsnLen* bytesDecoded _AND_
jmp_buf env)
{
    int   i;
    long int   retVal;
    unsigned long int  byte;


    if ( len > sizeof(AsnInt))
    {
        Asn1Error("BDecAsnIntContent: ERROR - integer to big to decode.\n");
        longjmp(env, -7);
    }


    byte =  (unsigned long int) BufGetByte(b);

    if (byte & 0x80)
        retVal = (-1 << 8) | byte;
    else
        retVal = byte;


    for (i = 1; i < len; i++)
        retVal = (retVal << 8) | (unsigned long int)(BufGetByte(b));

    if (BufReadError(b))
    {
        Asn1Error( "BDecAsnIntContent: ERROR - decoded past end of data \n");
        longjmp(env, -8);
    }
    (*bytesDecoded) += len;

    *result = retVal;

}
