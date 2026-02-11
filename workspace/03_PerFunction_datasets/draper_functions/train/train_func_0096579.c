scaleFromLATTS( string sEllips, double phits, double &scale )
{
    if( EQUALN( sEllips.c_str(), "Sphere", 6 ) )
    {
        scale = cos(phits);
    }
    else
    {
        const IlwisEllips *piwEllips =  iwEllips;
        double e2 = 0.0;
        while ( piwEllips->pszIlwisEllips )
        {
            if( EQUALN( sEllips.c_str(), piwEllips->pszIlwisEllips, strlen(piwEllips->pszIlwisEllips) ) )
            {
                double a = piwEllips->semiMajor;
                double b = a * ( 1 - piwEllips->invFlattening);
                e2 = ( a*a - b*b ) /( a*a );
                break;
            }
            piwEllips++;
        }
        scale = cos(phits) / sqrt (1. - e2 * sin(phits) * sin(phits));
    }
}
