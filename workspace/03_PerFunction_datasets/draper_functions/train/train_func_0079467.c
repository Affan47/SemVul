exportToWkb( OGRwkbByteOrder eByteOrder,
                               unsigned char * pabyData ) const

{


    pabyData[0] = DB2_V72_UNFIX_BYTE_ORDER((unsigned char) eByteOrder);


    GUInt32 nGType = getGeometryType();

    if( eByteOrder == wkbNDR )
        nGType = CPL_LSBWORD32( nGType );
    else
        nGType = CPL_MSBWORD32( nGType );

    memcpy( pabyData + 1, &nGType, 4 );


    memcpy( pabyData+5, &x, 16 );

    if( nCoordDimension == 3 )
    {
        memcpy( pabyData + 5 + 16, &z, 8 );
    }


    if( OGR_SWAP( eByteOrder ) )
    {
        CPL_SWAPDOUBLE( pabyData + 5 );
        CPL_SWAPDOUBLE( pabyData + 5 + 8 );

        if( nCoordDimension == 3 )
            CPL_SWAPDOUBLE( pabyData + 5 + 16 );
    }

    return OGRERR_NONE;
}
