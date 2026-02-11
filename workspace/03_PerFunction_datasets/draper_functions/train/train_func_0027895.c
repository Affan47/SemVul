exportToXML( char **ppszRawXML,
                                         const char * pszDialect ) const

{
    CPLXMLNode *psXMLTree = NULL;

    if( IsGeographic() )
    {
        psXMLTree = exportGeogCSToXML( this );
    }
    else if( IsProjected() )
    {
        psXMLTree = exportProjCSToXML( this );
    }
    else
        return OGRERR_UNSUPPORTED_SRS;

    *ppszRawXML = CPLSerializeXMLTree( psXMLTree );
    CPLDestroyXMLNode( psXMLTree );

    return OGRERR_NONE;
}
