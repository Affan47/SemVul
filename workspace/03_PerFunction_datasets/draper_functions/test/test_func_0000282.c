trunc_f( float f,
         int   digit )
{
    int ipow,
        c;
    float expon,
          tmp;

    if ( fabs( f ) < 1.e-20 )
        return 0.0;

    if ( digit < 0 )
        digit = 1;

    if ( ! digit )
    {
        if ( f > 0.5 )
            return 1.0;
        else if ( f < 0.5 )
            return 0.0;
        else
            return ( int ) f;
    }

    c = digit - 1;
    expon = log10( f );
    ipow = expon > 0.0 ? expon : expon - 1;

    tmp = pow( 10.0, expon - ipow );
    tmp += ADVANCE;
    tmp *= pow( 10.0, c );
    tmp = ( int ) tmp;
    tmp *= pow( 10.0, ipow - c );

    return tmp;
}
