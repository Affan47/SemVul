gsb_real_safe_real_from_string ( const gchar *string )
{
    unsigned nb_digits = 0;
    gint64 mantissa = 0;
    gint8 sign = 0;
    gint8 dot_position = -1;
    const gchar *p = string;

    if ( !string)
        return error_real;
    if ( g_strstr_len ( string, -1, ERROR_REAL_STRING ) )
        return error_real;

    for ( ; ; )
    {
        if ( g_ascii_isdigit ( *p ) )
        {
            mantissa *= 10;
            mantissa += ( *p - '0' );
            if ( mantissa > G_MAXINT64 )
                return error_real;
            if ( sign == 0 ) sign = 1;
            ++nb_digits;
            ++p;

        }
        else if ( *p == 0 )
        {
			gsb_real result;
			result.mantissa = sign * mantissa;
            if ( mantissa == 0 )
                result.exponent = 0;
            else
                result.exponent = ( dot_position >= 0 )
                              ? nb_digits - dot_position
                              : 0;

            return result;
        }
        else if ( strchr ( ".", *p ) )
        {
            if ( dot_position >= 0 )
                return error_real;
            dot_position = nb_digits;
            p = g_utf8_find_next_char ( p, NULL );
        }
        else if ( strchr ( "-", *p ) )
        {
            if ( sign != 0 )
                return error_real;
            sign = -1;
            ++p;
        }
        else
        {
            return error_real;
        }
    }
}
