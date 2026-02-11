GDALSetColorEntry( GDALColorTableH hTable, int i,
                        const GDALColorEntry * poEntry )

{
    VALIDATE_POINTER0( hTable, "GDALSetColorEntry" );
    VALIDATE_POINTER0( poEntry, "GDALSetColorEntry" );

    ((GDALColorTable *) hTable)->SetColorEntry( i, poEntry );
}
