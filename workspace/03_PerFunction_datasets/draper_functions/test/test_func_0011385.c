VRTParseFilterSources( CPLXMLNode *psChild, const char *pszVRTPath )

{
    VRTSource *poSrc;

    if( EQUAL(psChild->pszValue,"KernelFilteredSource") )
    {
        poSrc = new VRTKernelFilteredSource();
        if( poSrc->XMLInit( psChild, pszVRTPath ) == CE_None )
            return poSrc;
        else
            delete poSrc;
    }

    return NULL;
}
