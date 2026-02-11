OSRSetIWMPolyconic( OGRSpatialReferenceH hSRS,
                           double dfLat1, double dfLat2,
                           double dfCenterLong,
                           double dfFalseEasting, double dfFalseNorthing )

{
    VALIDATE_POINTER1( hSRS, "OSRSetIWMPolyconic", CE_Failure );

    return ((OGRSpatialReference *) hSRS)->SetIWMPolyconic(
        dfLat1, dfLat2, dfCenterLong,
        dfFalseEasting, dfFalseNorthing );
}
