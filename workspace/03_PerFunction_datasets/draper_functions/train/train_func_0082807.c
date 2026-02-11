OpenDatabase(const char* pszLayerName)
{
    CPLString osTableName;
    CPLString osEscapedName;
    if (pszLayerName)
    {
        osTableName = pszLayerName;
        char* pszEscapedName = CPLEscapeString(pszLayerName, -1, CPLES_URL);
        osEscapedName = pszEscapedName;
        CPLFree(pszEscapedName);
    }
    else
    {
        char* pszURL = CPLStrdup(osURL);
        char* pszLastSlash = strrchr(pszURL, '/');
        if (pszLastSlash)
        {
            osEscapedName = pszLastSlash + 1;
            char* pszName = CPLUnescapeString(osEscapedName, NULL, CPLES_URL);
            osTableName = pszName;
            CPLFree(pszName);
            *pszLastSlash = 0;
        }
        osURL = pszURL;
        CPLFree(pszURL);
        pszURL = NULL;

        if (pszLastSlash == NULL)
            return NULL;
    }

    CPLString osURI("/");
    osURI += osEscapedName;

    json_object* poAnswerObj = GET(osURI);
    if (poAnswerObj == NULL)
        return NULL;

    if ( !json_object_is_type(poAnswerObj, json_type_object) ||
            json_object_object_get(poAnswerObj, "db_name") == NULL )
    {
        IsError(poAnswerObj, "Database opening failed");

        json_object_put(poAnswerObj);
        return NULL;
    }

    OGRCouchDBTableLayer* poLayer = new OGRCouchDBTableLayer(this, osTableName);

    if ( json_object_object_get(poAnswerObj, "update_seq") != NULL )
    {
        int nUpdateSeq = json_object_get_int(json_object_object_get(poAnswerObj, "update_seq"));
        poLayer->SetUpdateSeq(nUpdateSeq);
    }

    json_object_put(poAnswerObj);

    papoLayers = (OGRLayer**) CPLRealloc(papoLayers, (nLayers + 1) * sizeof(OGRLayer*));
    papoLayers[nLayers ++] = poLayer;

    return poLayer;
}
