SPrintArray( GDALDataType eDataType, const void *paDataArray,
                          int nValues, const char *pszDelimiter )
{
    char        *pszString, *pszField;
    int         i, iFieldSize, iStringSize;

    iFieldSize = 32 + strlen( pszDelimiter );
    pszField = (char *)CPLMalloc( iFieldSize + 1 );
    iStringSize = nValues * iFieldSize + 1;
    pszString = (char *)CPLMalloc( iStringSize );
    memset( pszString, 0, iStringSize );
    for ( i = 0; i < nValues; i++ )
    {
        switch ( eDataType )
        {
            case GDT_Byte:
                sprintf( pszField, "%d%s", ((GByte *)paDataArray)[i],
                     (i < nValues - 1)?pszDelimiter:"" );
                break;
            case GDT_UInt16:
                sprintf( pszField, "%u%s", ((GUInt16 *)paDataArray)[i],
                     (i < nValues - 1)?pszDelimiter:"" );
                break;
            case GDT_Int16:
            default:
                sprintf( pszField, "%d%s", ((GInt16 *)paDataArray)[i],
                     (i < nValues - 1)?pszDelimiter:"" );
                break;
            case GDT_UInt32:
                sprintf( pszField, "%u%s", ((GUInt32 *)paDataArray)[i],
                     (i < nValues - 1)?pszDelimiter:"" );
                break;
            case GDT_Int32:
                sprintf( pszField, "%d%s", ((GInt32 *)paDataArray)[i],
                     (i < nValues - 1)?pszDelimiter:"" );
                break;
            case GDT_Float32:
                sprintf( pszField, "%.10g%s", ((float *)paDataArray)[i],
                     (i < nValues - 1)?pszDelimiter:"" );
                break;
            case GDT_Float64:
                sprintf( pszField, "%.15g%s", ((double *)paDataArray)[i],
                     (i < nValues - 1)?pszDelimiter:"" );
                break;
        }
        strcat( pszString, pszField );
    }

    CPLFree( pszField );
    return pszString;
}
