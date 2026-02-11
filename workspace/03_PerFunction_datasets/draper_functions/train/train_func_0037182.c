GetFeature( int nRecordId )

{
    char        achRecord[OGR_TIGER_RECBUF_LEN];

    if (psRTInfo == NULL)
        return NULL;

    if( nRecordId < 0 || nRecordId >= nFeatures )
    {
        CPLError( CE_Failure, CPLE_FileIO,
                  "Request for out-of-range feature %d of %s",
                  nRecordId, pszModule );
        return NULL;
    }


    if( fpPrimary == NULL )
        return NULL;

    if( VSIFSeekL( fpPrimary, nRecordId * nRecordLength, SEEK_SET ) != 0 )
    {
        CPLError( CE_Failure, CPLE_FileIO,
                  "Failed to seek to %d of %s",
                  nRecordId * nRecordLength, pszModule );
        return NULL;
    }

    if( VSIFReadL( achRecord, psRTInfo->nRecordLength, 1, fpPrimary ) != 1 )
    {
        CPLError( CE_Failure, CPLE_FileIO,
                  "Failed to read record %d of %s",
                  nRecordId, pszModule );
        return NULL;
    }


    OGRFeature  *poFeature = new OGRFeature( poFeatureDefn );

    SetFields( psRTInfo, poFeature, achRecord );

    return poFeature;
}
