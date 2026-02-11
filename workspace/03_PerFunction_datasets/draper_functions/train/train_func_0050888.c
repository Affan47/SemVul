push_back( unicode_char val )
    {
        code_point cp[2] = {
            0, 0
        };
        size_t c = _utf32_to_utf16( val, cp );
        if ( c > 0 ) push_back( cp[0] );
        if ( c > 1 ) push_back( cp[1] );
    }
