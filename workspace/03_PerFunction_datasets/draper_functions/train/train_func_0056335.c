SerializeToXML( const char *pszVRTPath )

{
    CPLXMLNode *psSrc = VRTSimpleSource::SerializeToXML( pszVRTPath );

    if( psSrc == NULL )
        return NULL;

    CPLFree( psSrc->pszValue );
    psSrc->pszValue = CPLStrdup( "ComplexSource" );

    if( bNoDataSet )
    {
        if (CPLIsNan(dfNoDataValue))
            CPLSetXMLValue( psSrc, "NODATA", "nan");
        else
            CPLSetXMLValue( psSrc, "NODATA",
                            CPLSPrintf("%g", dfNoDataValue) );
    }

    if( bDoScaling )
    {
        CPLSetXMLValue( psSrc, "ScaleOffset",
                        CPLSPrintf("%g", dfScaleOff) );
        CPLSetXMLValue( psSrc, "ScaleRatio",
                        CPLSPrintf("%g", dfScaleRatio) );
    }

    if ( nLUTItemCount )
    {
        CPLString osLUT = CPLString().Printf("%g:%g", padfLUTInputs[0], padfLUTOutputs[0]);
        int i;
        for ( i = 1; i < nLUTItemCount; i++ )
            osLUT += CPLString().Printf(",%g:%g", padfLUTInputs[i], padfLUTOutputs[i]);
        CPLSetXMLValue( psSrc, "LUT", osLUT );
    }

    if ( nColorTableComponent )
    {
        CPLSetXMLValue( psSrc, "ColorTableComponent",
                        CPLSPrintf("%d", nColorTableComponent) );
    }

    return psSrc;
}
