Create( const char * pszFilename,
                                 int nXSize, int nYSize, int nBands,
                                 GDALDataType eType,
                                 char ** papszOptions )

{
    if( eType != GDT_Byte && eType != GDT_Int16 )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Attempt to create .GIS file with unsupported data type '%s'.",
                  GDALGetDataTypeName( eType ) );
        return NULL;
    }


    VSILFILE	*fp;

    fp = VSIFOpenL( pszFilename, "wb" );

    if( fp == NULL )
    {
        CPLError( CE_Failure, CPLE_OpenFailed,
                  "Attempt to create file `%s' failed.\n",
                  pszFilename );
        return NULL;
    }


    unsigned char abyHeader[128];
    GInt16  n16Val;
    GInt32  n32Val;

    memset( abyHeader, 0, sizeof(abyHeader) );

    memcpy( abyHeader + 0, "HEAD74", 6 );


    if( eType == GDT_Byte )
        n16Val = 0;
    else
        n16Val = 2;
    memcpy( abyHeader + 6, &n16Val, 2 );


    n16Val = (GInt16) nBands;
    memcpy( abyHeader + 8, &n16Val, 2 );


    n32Val = nXSize;
    memcpy( abyHeader + 16, &n32Val, 4 );


    n32Val = nYSize;
    memcpy( abyHeader + 20, &n32Val, 4 );


    n16Val = 0;
    memcpy( abyHeader + 88, &n16Val, 2 );


    n16Val = 0;
    memcpy( abyHeader + 90, &n16Val, 2 );


    n16Val = 0;
    memcpy( abyHeader + 106, &n16Val, 2 );


    float f32Val;

    f32Val = 0.0f;
    memcpy( abyHeader + 108, &f32Val, 4 );


    f32Val = 0.5f;
    memcpy( abyHeader + 112, &f32Val, 4 );


    f32Val = (float) (nYSize - 0.5);
    memcpy( abyHeader + 116, &f32Val, 4 );


    f32Val = 1.0f;
    memcpy( abyHeader + 120, &f32Val, 4 );


    f32Val = 1.0f;
    memcpy( abyHeader + 124, &f32Val, 4 );

    VSIFWriteL( abyHeader, sizeof(abyHeader), 1, fp );


    vsi_l_offset nImageBytes;

    if( eType != GDT_Byte )
        nImageBytes = nXSize * (vsi_l_offset) nYSize * 2;
    else
        nImageBytes = nXSize * (vsi_l_offset) nYSize;

    memset( abyHeader, 0, sizeof(abyHeader) );

    while( nImageBytes > 0 )
    {
        vsi_l_offset nWriteThisTime = MIN(nImageBytes,sizeof(abyHeader));

        if( VSIFWriteL( abyHeader, 1, (size_t)nWriteThisTime, fp )
            != nWriteThisTime )
        {
            VSIFCloseL( fp );
            CPLError( CE_Failure, CPLE_FileIO,
                      "Failed to write whole Istar file." );
            return NULL;
        }
        nImageBytes -= nWriteThisTime;
    }

    VSIFCloseL( fp );

    return (GDALDataset *) GDALOpen( pszFilename, GA_Update );
}
