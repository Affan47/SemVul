PamClear()

{
    if( psPam )
    {
        CPLFree( psPam->pszPamFilename );
        CPLFree( psPam->pszProjection );
        CPLFree( psPam->pszGCPProjection );
        if( psPam->nGCPCount > 0 )
        {
            GDALDeinitGCPs( psPam->nGCPCount, psPam->pasGCPList );
            CPLFree( psPam->pasGCPList );
        }

        delete psPam;
        psPam = NULL;
    }
}
