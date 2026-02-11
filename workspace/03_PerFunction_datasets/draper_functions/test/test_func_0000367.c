GetNoDataValue( int *pbSuccess )

{
    if( pbSuccess != NULL )
        *pbSuccess = TRUE;

    if( eDataType == GDT_Float32 )
        return ESRI_GRID_FLOAT_NO_DATA;
    else if( eDataType == GDT_Int16 )
        return -32768;
    else if( eDataType == GDT_Byte )
        return 255;
    else
        return ESRI_GRID_NO_DATA;
}
