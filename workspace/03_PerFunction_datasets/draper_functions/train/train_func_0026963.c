ExploreTree(GDALPDFObject* poObj, int nRecLevel)
{
    if (nRecLevel == 16)
        return;

    if (poObj->GetType() != PDFObjectType_Dictionary)
        return;

    GDALPDFDictionary* poDict = poObj->GetDictionary();

    GDALPDFObject* poS = poDict->Get("S");
    CPLString osS;
    if (poS != NULL && poS->GetType() == PDFObjectType_Name)
    {
        osS = poS->GetName();
    }

    GDALPDFObject* poT = poDict->Get("T");
    CPLString osT;
    if (poT != NULL && poT->GetType() == PDFObjectType_String)
    {
        osT = poT->GetString();
    }

    GDALPDFObject* poK = poDict->Get("K");
    if (poK == NULL)
        return;

    if (poK->GetType() == PDFObjectType_Array)
    {
        GDALPDFArray* poArray = poK->GetArray();
        if (poArray->GetLength() > 0 &&
            poArray->Get(0)->GetType() == PDFObjectType_Dictionary &&
            poArray->Get(0)->GetDictionary()->Get("K") != NULL &&
            poArray->Get(0)->GetDictionary()->Get("K")->GetType() == PDFObjectType_Int)
        {
            CPLString osLayerName;
            if (osT.size())
                osLayerName = osT;
            else
            {
                if (osS.size())
                    osLayerName = osS;
                else
                    osLayerName = CPLSPrintf("Layer%d", nLayers + 1);
            }

            const char* pszWKT = poGDAL_DS->GetProjectionRef();
            OGRSpatialReference* poSRS = NULL;
            if (pszWKT && pszWKT[0] != '\0')
            {
                poSRS = new OGRSpatialReference();
                poSRS->importFromWkt((char**) &pszWKT);
            }

            OGRPDFLayer* poLayer =
                new OGRPDFLayer(this, osLayerName.c_str(), poSRS, wkbUnknown);
            delete poSRS;

            poLayer->Fill(poArray);

            papoLayers = (OGRLayer**)
                CPLRealloc(papoLayers, (nLayers + 1) * sizeof(OGRLayer*));
            papoLayers[nLayers] = poLayer;
            nLayers ++;
        }
        else
        {
            for(int i=0;i<poArray->GetLength();i++)
                ExploreTree(poArray->Get(i), nRecLevel + 1);
        }
    }
    else if (poK->GetType() == PDFObjectType_Dictionary)
    {
        ExploreTree(poK, nRecLevel + 1);
    }
}
