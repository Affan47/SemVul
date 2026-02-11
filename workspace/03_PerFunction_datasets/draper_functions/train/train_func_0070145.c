BDecUAsnIntContent PARAMS((b, tag, len, result, bytesDecoded, env),
BUF_TYPE b _AND_
AsnTag   tag _AND_
AsnLen   len _AND_
UAsnInt* result _AND_
AsnLen*  bytesDecoded _AND_
jmp_buf  env)
{
    int   i;
    unsigned long int retVal;

    retVal =  (unsigned long int) BufGetByte(b);

    if ( len > (sizeof(UAsnInt)+1))
    {
        Asn1Error("BDecUAsnIntContent: ERROR - integer to big to decode.\n");
        longjmp(env, -9);
    }
    else if (retVal & 0x80)
    {
        Asn1Error("BDecUAsnIntContent: ERROR - integer is negative.\n");
        longjmp(env, -10);
    }
    else if ( (len == (sizeof(UAsnInt)+1)) && (retVal != 0) )
    {


        Asn1Error("BDecUAsnIntContent: ERROR - integer is negative.\n");
        longjmp(env, -11);
    }


    for (i = 1; i < len; i++)
        retVal = (retVal << 8) | (unsigned long int)(BufGetByte(b));

    if (BufReadError(b))
    {
        Asn1Error( "BDecUIntegerContent: ERROR - decoded past end of data\n");
        longjmp(env, -12);
    }
    (*bytesDecoded) += len;

    *result = retVal;

}
