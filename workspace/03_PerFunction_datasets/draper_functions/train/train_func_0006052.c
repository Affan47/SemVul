GetNextFeature()

{
    OGRFeature  *poFeature = NULL;


    if( iCurrentReader == poDS->GetFileCount() )
        return NULL;


    if( iCurrentReader == -1 )
    {
        iCurrentReader++;
        nCurrentPos = -1;
    }

    NTFFileReader       *poCurrentReader = poDS->GetFileReader(iCurrentReader);
    if( poCurrentReader->GetFP() == NULL )
    {
        poCurrentReader->Open();
    }


    if( nCurrentPos != -1 )
        poCurrentReader->SetFPPos( nCurrentPos, nCurrentFID );
    else
        poCurrentReader->Reset();


    while( TRUE )
    {
        poFeature = poCurrentReader->ReadOGRFeature( this );
        if( poFeature == NULL )
            break;

        m_nFeaturesRead++;

        if( (m_poFilterGeom == NULL
             || poFeature->GetGeometryRef() == NULL
             || FilterGeometry( poFeature->GetGeometryRef() ) )
            && (m_poAttrQuery == NULL
                || m_poAttrQuery->Evaluate( poFeature )) )
            break;

        delete poFeature;
    }


    if( poFeature == NULL )
    {
        poCurrentReader->Close();

        if( poDS->GetOption("CACHING") != NULL
            && EQUAL(poDS->GetOption("CACHING"),"OFF") )
        {
            poCurrentReader->DestroyIndex();
        }

        do {
            iCurrentReader++;
        } while( iCurrentReader < poDS->GetFileCount()
                 && !poDS->GetFileReader(iCurrentReader)->TestForLayer(this) );

        nCurrentPos = -1;
        nCurrentFID = 1;

        poFeature = GetNextFeature();
    }
    else
    {
        poCurrentReader->GetFPPos(&nCurrentPos, &nCurrentFID);
    }

    return poFeature;
}
