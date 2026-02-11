rotate( FL_POINT * p,
        int        n,
        int        angle,
        int        xo,
        int        yo )
{
    static int last_angle;
    static double sina = 0,
                  cosa = 1;
    int i,
        tx,
        ty;

    if ( angle == 0 || angle == 3600 )
        return;

    if ( last_angle != angle )
    {
        last_angle = angle;
        sina = sin( angle * M_PI / 1800.0 );
        cosa = cos( angle * M_PI / 1800.0 );
    }

    for ( i = 0; i < n; i++ )
    {
        tx = p[ i ].x - xo;
        ty = p[ i ].y - yo;
        p[ i ].x = xo + tx * cosa + ty * sina + 0.5;
        p[ i ].y = yo - tx * sina + ty * cosa + 0.5;
    }
}
