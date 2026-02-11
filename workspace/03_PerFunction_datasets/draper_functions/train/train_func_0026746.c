IsCityGMLGenericAttributeElement( const char *pszElement, void* attr )

{
    if( strcmp(pszElement, "stringAttribute") != 0 &&
        strcmp(pszElement, "intAttribute") != 0 &&
        strcmp(pszElement, "doubleAttribute") != 0 )
        return FALSE;

    char* pszVal = m_poGMLHandler->GetAttributeValue(attr, "name");
    if (pszVal == NULL)
        return FALSE;

    GMLFeatureClass *poClass = m_poState->m_poFeature->GetClass();


    if( !poClass->IsSchemaLocked() )
    {
        CPLFree(pszVal);
        return TRUE;
    }

    for( int i = 0; i < poClass->GetPropertyCount(); i++ )
    {
        if( strcmp(poClass->GetProperty(i)->GetSrcElement(),pszVal) == 0 )
        {
            CPLFree(pszVal);
            return TRUE;
        }
    }

    CPLFree(pszVal);
    return FALSE;
}
