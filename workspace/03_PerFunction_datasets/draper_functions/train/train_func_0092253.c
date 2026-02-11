GetFeature( const char* pszId )
{
    GetLayerDefn();

    CPLString osURI("/");
    osURI += osEscapedName;
    osURI += "/";
    osURI += pszId;
    json_object* poAnswerObj = poDS->GET(osURI);
    if (poAnswerObj == NULL)
        return NULL;

    if ( !json_object_is_type(poAnswerObj, json_type_object) )
    {
        CPLError(CE_Failure, CPLE_AppDefined, "GetFeature(%s) failed",
                 pszId);
        json_object_put(poAnswerObj);
        return NULL;
    }

    if ( poDS->IsError(poAnswerObj, CPLSPrintf("GetFeature(%s) failed", pszId)) )
    {
        json_object_put(poAnswerObj);
        return NULL;
    }

    OGRFeature* poFeature = TranslateFeature( poAnswerObj );

    json_object_put( poAnswerObj );

    return poFeature;
}
