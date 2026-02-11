ReleaseDataSource( OGRDataSource * poDS )

{
    {
        CPLMutexHolderD( &hDRMutex );

        int iDS;

        for( iDS = 0; iDS < nOpenDSCount; iDS++ )
        {
            if( poDS == papoOpenDS[iDS] )
                break;
        }

        if( iDS == nOpenDSCount )
        {
            CPLDebug( "OGR",
                      "ReleaseDataSource(%s/%p) on unshared datasource!\n"
                      "Deleting directly.",
                      poDS->GetName(), poDS );
            delete poDS;
            return OGRERR_FAILURE;
        }

        if( poDS->GetRefCount() > 0 )
            poDS->Dereference();

        if( poDS->GetRefCount() > 0 )
        {
            CPLDebug( "OGR",
                      "ReleaseDataSource(%s/%p) ... just dereferencing.",
                      poDS->GetName(), poDS );
            return OGRERR_NONE;
        }

        if( poDS->GetSummaryRefCount() > 0 )
        {
            CPLDebug( "OGR",
                      "OGRSFDriverRegistrar::ReleaseDataSource(%s)\n"
                      "Datasource reference count is now zero, but some layers\n"
                      "are still referenced ... not closing datasource.",
                      poDS->GetName() );
            return OGRERR_FAILURE;
        }


        CPLDebug( "OGR",
                  "ReleaseDataSource(%s/%p) dereferenced and now destroying.",
                  poDS->GetName(), poDS );

        CPLFree( papszOpenDSRawName[iDS] );
        memmove( papszOpenDSRawName + iDS, papszOpenDSRawName + iDS + 1,
                 sizeof(char *) * (nOpenDSCount - iDS - 1) );
        memmove( papoOpenDS + iDS, papoOpenDS + iDS + 1,
                 sizeof(char *) * (nOpenDSCount - iDS - 1) );
        memmove( papoOpenDSDriver + iDS, papoOpenDSDriver + iDS + 1,
                 sizeof(char *) * (nOpenDSCount - iDS - 1) );
        memmove( panOpenDSPID + iDS, panOpenDSPID + iDS + 1,
                 sizeof(GIntBig) * (nOpenDSCount - iDS - 1) );

        nOpenDSCount--;

        if( nOpenDSCount == 0 )
        {
            CPLFree( papszOpenDSRawName );
            papszOpenDSRawName = NULL;
            CPLFree( papoOpenDS );
            papoOpenDS = NULL;
            CPLFree( papoOpenDSDriver );
            papoOpenDSDriver = NULL;
            CPLFree( panOpenDSPID );
            panOpenDSPID = NULL;
        }
    }


    delete poDS;

    return OGRERR_NONE;
}
