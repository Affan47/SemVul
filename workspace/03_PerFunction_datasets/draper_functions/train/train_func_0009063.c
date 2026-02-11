importFromWkb( unsigned char * pabyData,
                                  int nSize )

{
    OGRwkbByteOrder     eByteOrder;
    int                 nDataOffset, b3D;

    if( nSize < 9 && nSize != -1 )
        return OGRERR_NOT_ENOUGH_DATA;


    eByteOrder = DB2_V72_FIX_BYTE_ORDER((OGRwkbByteOrder) *pabyData);
    if (!( eByteOrder == wkbXDR || eByteOrder == wkbNDR ))
        return OGRERR_CORRUPT_DATA;


#ifdef DEBUG
    OGRwkbGeometryType eGeometryType;

    if( eByteOrder == wkbNDR )
        eGeometryType = (OGRwkbGeometryType) pabyData[1];
    else
        eGeometryType = (OGRwkbGeometryType) pabyData[4];

    if( eGeometryType != wkbPolygon )
        return OGRERR_CORRUPT_DATA;
#endif

    if( eByteOrder == wkbNDR )
        b3D = pabyData[4] & 0x80 || pabyData[2] & 0x80;
    else
        b3D = pabyData[1] & 0x80 || pabyData[3] & 0x80;

    if( b3D )
        nCoordDimension = 3;
    else
        nCoordDimension = 2;


    if( nRingCount != 0 )
    {
        for( int iRing = 0; iRing < nRingCount; iRing++ )
            delete papoRings[iRing];

        OGRFree( papoRings );
        papoRings = NULL;
    }


    memcpy( &nRingCount, pabyData + 5, 4 );

    if( OGR_SWAP( eByteOrder ) )
        nRingCount = CPL_SWAP32(nRingCount);

    if (nRingCount < 0 || nRingCount > INT_MAX / 4)
    {
        nRingCount = 0;
        return OGRERR_CORRUPT_DATA;
    }


    if (nSize != -1 && nSize - 9 < nRingCount * 4)
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Length of input WKB is too small" );
        nRingCount = 0;
        return OGRERR_NOT_ENOUGH_DATA;
    }

    papoRings = (OGRLinearRing **) VSIMalloc2(sizeof(void*), nRingCount);
    if (nRingCount != 0 && papoRings == NULL)
    {
        nRingCount = 0;
        return OGRERR_NOT_ENOUGH_MEMORY;
    }

    nDataOffset = 9;
    if( nSize != -1 )
        nSize -= nDataOffset;


    for( int iRing = 0; iRing < nRingCount; iRing++ )
    {
        OGRErr  eErr;

        papoRings[iRing] = new OGRLinearRing();
        eErr = papoRings[iRing]->_importFromWkb( eByteOrder, b3D,
                                                 pabyData + nDataOffset,
                                                 nSize );
        if( eErr != OGRERR_NONE )
        {
            delete papoRings[iRing];
            nRingCount = iRing;
            return eErr;
        }

        if( nSize != -1 )
            nSize -= papoRings[iRing]->_WkbSize( b3D );

        nDataOffset += papoRings[iRing]->_WkbSize( b3D );
    }

    return OGRERR_NONE;
}
