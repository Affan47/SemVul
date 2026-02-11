SetUnitType( const char *pszNewValue )

{
    ((VRTDataset *) poDS)->SetNeedsFlush();

    CPLFree( pszUnitType );

    if( pszNewValue == NULL )
        pszUnitType = NULL;
    else
        pszUnitType = CPLStrdup(pszNewValue);

    return CE_None;
}
