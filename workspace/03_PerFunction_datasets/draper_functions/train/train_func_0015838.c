PDSConvertFromHex(const char* pszVal)
{
    if( !EQUALN(pszVal, "16#", 3) )
        return 0;

    pszVal += 3;
    GUInt32 nVal = 0;
    while( *pszVal != '#' && *pszVal != '\0' )
    {
        nVal <<= 4;
        if( *pszVal >= '0' && *pszVal <= '9' )
            nVal += *pszVal - '0';
        else if( *pszVal >= 'A' && *pszVal <= 'F' )
            nVal += *pszVal - 'A' + 10;
        else
            return 0;
        pszVal ++;
    }
    return nVal;
}
