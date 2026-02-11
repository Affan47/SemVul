inchi_ios_print_nodisplay( INCHI_IOSTREAM * ios, const char* lpszFormat, ... )
{
va_list argList;

    if (!ios)
        return -1;

    if (ios->type == INCHI_IOSTREAM_STRING)
    {

        int ret=0, max_len;
        my_va_start( argList, lpszFormat );
        max_len = GetMaxPrintfLength( lpszFormat, argList);
        va_end( argList );
        if ( max_len >= 0 )
        {
            if ( ios->s.nAllocatedLength - ios->s.nUsedLength <= max_len )
            {

                int  nAddLength = inchi_max( INCHI_ADD_STR_LEN, max_len );
                char *new_str = (char *)inchi_calloc( ios->s.nAllocatedLength + nAddLength, sizeof(new_str[0]) );
                if ( new_str )
                {
                    if ( ios->s.pStr )
                    {
                        if ( ios->s.nUsedLength > 0 )
                        {
                            memcpy( new_str, ios->s.pStr, sizeof(new_str[0])*ios->s.nUsedLength );
                        }
                        inchi_free( ios->s.pStr );
                    }
                    ios->s.pStr              = new_str;
                    ios->s.nAllocatedLength += nAddLength;
                } else
                {
                    return -1;
                }
            }

            my_va_start( argList, lpszFormat );
            ret = vsprintf( ios->s.pStr + ios->s.nUsedLength, lpszFormat, argList );
            va_end(argList);
            if ( ret >= 0 )
            {
                ios->s.nUsedLength += ret;
            }
            return ret;
        }
        return -1;
    }

    else if (ios->type == INCHI_IOSTREAM_FILE)
    {
        my_va_start( argList, lpszFormat );
        inchi_print_nodisplay( ios->f, lpszFormat, argList);
        va_end(argList);
    }


    return 0;
}
