CreateFeature (
    OGRFeature * poOgrFeat )
{

    if ( !bUpdate )
        return OGRERR_UNSUPPORTED_OPERATION;

    PlacemarkPtr poKmlPlacemark =
        feat2kml ( m_poOgrDS, this, poOgrFeat, m_poOgrDS->GetKmlFactory (  ) );

    m_poKmlLayer->add_feature ( poKmlPlacemark );


    nFeatures++;


    bUpdated = TRUE;
    m_poOgrDS->Updated (  );

    return OGRERR_NONE;
}
