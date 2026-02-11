GetLayerByName(const char * pszLayerNameIn)
{
#ifndef IMMEDIATE_OPENING
    if (oVectorLayerName.size() != 0)
    {
        int j;
        for(j=0;j<nLayers;j++)
        {
            if (strcmp(papoLayers[j]->GetName(), pszLayerNameIn) == 0)
            {
                return papoLayers[j];
            }
        }

        size_t i;
        for(j = 0; j < 2; j++)
        {
            for(i = 0; i < oVectorLayerName.size(); i++)
            {
                const char* pszFilename = oVectorLayerName[i].c_str();
                const char* pszLayerName = CPLGetBasename(pszFilename);

                if (j == 0)
                {
                    if (strcmp(pszLayerName, pszLayerNameIn) != 0)
                        continue;
                }
                else
                {
                    if ( !EQUAL(pszLayerName, pszLayerNameIn) )
                        continue;
                }

                if( !OpenFile( pszFilename, bDSUpdate, TRUE ) )
                {
                    CPLError( CE_Failure, CPLE_OpenFailed,
                            "Failed to open file %s.\n"
                            "It may be corrupt or read-only file accessed in update mode.\n",
                            pszFilename );
                    return NULL;
                }
                else
                {
                    return papoLayers[nLayers - 1];
                }
            }
        }

        return NULL;
    }
#endif

    return OGRDataSource::GetLayerByName(pszLayerNameIn);
}
