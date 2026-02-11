n2n_parse_hex( uint8_t * keyBuf,
                       size_t keyLen,
                       const char * textKey,
                       size_t textLen)
{
    ssize_t retval=0;
    uint8_t * pout=keyBuf;
    size_t octet=0;
    const char * textEnd;
    const char * pbeg;

    textEnd = textKey+textLen;
    pbeg=textKey;

    while ( ( pbeg + 1 < textEnd ) && ( retval < (ssize_t)keyLen ) )
    {
      if ( 1 != sscanf( pbeg, "%02x", (unsigned int*)&octet ) )
        {
            retval=-1;
            break;
        }

        *pout = (octet & 0xff);
        ++pout;
        ++retval;
        pbeg += 2;
    }

    return retval;
}
