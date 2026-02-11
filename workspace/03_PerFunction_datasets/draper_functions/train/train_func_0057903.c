_dxfSaveHardwareWindow(char *where)
{
    Private           cacheObject = NULL;
    tdmChildGlobalP   globals = NULL;
    char*             cacheId = NULL;
    tdmParsedFormatT* pFormat = NULL;
    Field             image = NULL;


    if (!(pFormat = _tdmParseDisplayString (where, &cacheId)))
        goto error;


    if (!(_validateDisplayString(pFormat, 1)))
        goto error ;


    cacheObject = (Private) DXGetCacheEntry(cacheId, 0, 0);
    if (! cacheObject) {
        DXSetError(ERROR_BAD_PARAMETER,
                   "window matching \"%s\" not found", where);
        goto error;
    } else {
        globals = (tdmChildGlobalP) DXGetPrivateData(cacheObject) ;
        image = _dxfCaptureHardwareImage(globals);
        if (! image)
            goto error;
    }


error:
    if (pFormat)
        _dxfDeleteParsedDisplayString(pFormat);

    if (cacheId)
        tdmFree(cacheId);


    if(cacheObject)
        DXDelete((Pointer)cacheObject) ;

    return (dxObject)image;
}
