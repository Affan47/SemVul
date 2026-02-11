ExploreLayer(CPLXMLNode* psXML,
                                      CPLString osFormat,
                                      CPLString osTransparent,
                                      const char* pszSRS,
                                      const char* pszMinX,
                                      const char* pszMinY,
                                      const char* pszMaxX,
                                      const char* pszMaxY)
{
    const char* pszName = CPLGetXMLValue(psXML, "Name", NULL);
    const char* pszTitle = CPLGetXMLValue(psXML, "Title", NULL);
    const char* pszAbstract = CPLGetXMLValue(psXML, "Abstract", NULL);

    const char* pszSRSLocal = NULL;
    const char* pszMinXLocal = NULL;
    const char* pszMinYLocal = NULL;
    const char* pszMaxXLocal = NULL;
    const char* pszMaxYLocal = NULL;

    const char* pszSRSTagName =
        VersionStringToInt(osVersion.c_str()) >= VersionStringToInt("1.3.0") ? "CRS" : "SRS";


    CPLXMLNode* psSRS = CPLGetXMLNode( psXML, "BoundingBox" );
    if (psSRS == NULL)
    {
        psSRS = CPLGetXMLNode( psXML, "LatLonBoundingBox" );
        pszSRSLocal = CPLGetXMLValue(psXML, pszSRSTagName, NULL);
        if (pszSRSLocal == NULL)
            pszSRSLocal = "EPSG:4326";
    }
    else
        pszSRSLocal = CPLGetXMLValue(psSRS, pszSRSTagName, NULL);

    if (pszSRSLocal != NULL && psSRS != NULL)
    {
        pszMinXLocal = CPLGetXMLValue(psSRS, "minx", NULL);
        pszMinYLocal = CPLGetXMLValue(psSRS, "miny", NULL);
        pszMaxXLocal = CPLGetXMLValue(psSRS, "maxx", NULL);
        pszMaxYLocal = CPLGetXMLValue(psSRS, "maxy", NULL);

        if (pszMinXLocal && pszMinYLocal && pszMaxXLocal && pszMaxYLocal)
        {
            pszSRS = pszSRSLocal;
            pszMinX = pszMinXLocal;
            pszMinY = pszMinYLocal;
            pszMaxX = pszMaxXLocal;
            pszMaxY = pszMaxYLocal;
        }
    }

    if (pszName != NULL && pszSRS && pszMinX && pszMinY && pszMaxX && pszMaxY)
    {
        CPLString osLocalTransparent(osTransparent);
        if (osLocalTransparent.size() == 0)
        {
            const char* pszOpaque = CPLGetXMLValue(psXML, "opaque", "0");
            if (EQUAL(pszOpaque, "1"))
                osLocalTransparent = "FALSE";
        }

        WMSCKeyType oWMSCKey(pszName, pszSRS);
        std::map<WMSCKeyType, WMSCTileSetDesc>::iterator oIter = osMapWMSCTileSet.find(oWMSCKey);
        if (oIter != osMapWMSCTileSet.end())
        {
            AddWMSCSubDataset(oIter->second, pszTitle, osLocalTransparent);
        }
        else
        {
            AddSubDataset(pszName, pszTitle, pszAbstract,
                          pszSRS, pszMinX, pszMinY,
                          pszMaxX, pszMaxY, osFormat, osLocalTransparent);
        }
    }

    CPLXMLNode* psIter = psXML->psChild;
    for(; psIter != NULL; psIter = psIter->psNext)
    {
        if (psIter->eType == CXT_Element)
        {
            if (EQUAL(psIter->pszValue, "Layer"))
                ExploreLayer(psIter, osFormat, osTransparent,
                             pszSRS, pszMinX, pszMinY, pszMaxX, pszMaxY);
        }
    }
}
