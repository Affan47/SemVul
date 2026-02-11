SetUnitType( const char *pszUnitType )
{
    IdrisiDataset *poGDS = (IdrisiDataset *) poDS;

    if( strlen( pszUnitType ) == 0 )
    {
        poGDS->papszRDC =
            CSLSetNameValue( poGDS->papszRDC, rdcVALUE_UNITS, "unspecified" );
    }
    else
    {
        poGDS->papszRDC =
            CSLSetNameValue( poGDS->papszRDC, rdcVALUE_UNITS, pszUnitType );
    }

    return CE_None;
}
