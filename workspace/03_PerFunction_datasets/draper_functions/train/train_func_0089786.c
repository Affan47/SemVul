Alpha(REAL pos) const
{
    CHECKWALL;

    REAL diff = ( endDist_  - begDist_ );
    REAL a = pos - begDist_;

    if ( diff > 0 )
        a /= diff;

    tASSERT ( -.001 < a );
    tASSERT ( 1.001 > a );

    return a;
}
