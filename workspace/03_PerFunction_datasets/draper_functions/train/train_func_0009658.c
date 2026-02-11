OGR2SQLITE_GoToWishedIndex(OGR2SQLITE_vtab_cursor* pMyCursor)
{
    if( pMyCursor->nFeatureCount >= 0 )
    {
        if( pMyCursor->nCurFeatureIndex < pMyCursor->nNextWishedIndex )
        {
            do
            {
                pMyCursor->nCurFeatureIndex ++;

                delete pMyCursor->poFeature;
                pMyCursor->poFeature = pMyCursor->poLayer->GetNextFeature();
#ifdef DEBUG_OGR2SQLITE
                CPLDebug("OGR2SQLITE", "GetNextFeature() --> %d",
                    pMyCursor->poFeature ? (int)pMyCursor->poFeature->GetFID() : -1);
#endif
            }
            while( pMyCursor->nCurFeatureIndex < pMyCursor->nNextWishedIndex );

            CPLFree(pMyCursor->pabyGeomBLOB);
            pMyCursor->pabyGeomBLOB = NULL;
            pMyCursor->nGeomBLOBLen = -1;
        }
    }
}
