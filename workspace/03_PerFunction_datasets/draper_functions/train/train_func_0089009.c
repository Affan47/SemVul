GetSpatialRef()

{
    if (nSRSId == UNDETERMINED_SRID)
        GetLayerDefn();

    if( poSRS == NULL && nSRSId > 0 )
    {
        poSRS = poDS->FetchSRS( nSRSId );
        if( poSRS != NULL )
            poSRS->Reference();
    }

    return poSRS;
}
