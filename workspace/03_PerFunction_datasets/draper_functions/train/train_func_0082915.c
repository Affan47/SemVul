IsRing(  ) const

{
#ifndef HAVE_GEOS

    return FALSE;

#else

    OGRBoolean bResult = FALSE;
    GEOSGeom hThisGeosGeom = NULL;

    hThisGeosGeom = exportToGEOS();

    if( hThisGeosGeom != NULL  )
    {
        bResult = GEOSisRing( hThisGeosGeom );
        GEOSGeom_destroy( hThisGeosGeom );
    }

    return bResult;

#endif
}
