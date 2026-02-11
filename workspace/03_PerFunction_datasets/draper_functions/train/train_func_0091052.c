GetInstBytes( GByte *pabyData, int nDataSize )

{
    int		nCount;
    int		nInstBytes = 0;

    if( nBytes > -1 )
        return nBytes;

    if( chPointer != '\0' )
    {
        if (nDataSize < 4)
        {
            CPLError(CE_Failure, CPLE_AppDefined, "Buffer too small");
            return -1;
        }

        memcpy( &nCount, pabyData, 4 );
        HFAStandard( 4, &nCount );

        pabyData += 8;
        nInstBytes += 8;
    }
    else
        nCount = 1;

    if( chItemType == 'b' && nCount != 0 )
    {
        if (nDataSize - nInstBytes < 4+4+2)
        {
            CPLError(CE_Failure, CPLE_AppDefined, "Buffer too small");
            return -1;
        }

        GInt32 nRows, nColumns;
        GInt16 nBaseItemType;

        memcpy( &nRows, pabyData, 4 );
        HFAStandard( 4, &nRows );
        memcpy( &nColumns, pabyData+4, 4 );
        HFAStandard( 4, &nColumns );
        memcpy( &nBaseItemType, pabyData+8, 2 );
        HFAStandard( 2, &nBaseItemType );

        nInstBytes += 12;

        if (nRows < 0 || nColumns < 0)
            return -1;
        if (nColumns != 0 && nRows > INT_MAX / nColumns)
            return -1;
        if (nColumns != 0 && ((HFAGetDataTypeBits(nBaseItemType) + 7) / 8) * nRows > INT_MAX / nColumns)
            return -1;
        if (((HFAGetDataTypeBits(nBaseItemType) + 7) / 8) * nRows * nColumns > INT_MAX - nInstBytes)
            return -1;

        nInstBytes +=
            ((HFAGetDataTypeBits(nBaseItemType) + 7) / 8) * nRows * nColumns;
    }
    else if( poItemObjectType == NULL )
    {
        if (nCount != 0 && HFADictionary::GetItemSize(chItemType) > INT_MAX / nCount)
            return -1;
        nInstBytes += nCount * HFADictionary::GetItemSize(chItemType);
    }
    else
    {
        int		i;

        for( i = 0; i < nCount &&
                    nInstBytes < nDataSize &&
                    nInstBytes >= 0; i++ )
        {
            int	nThisBytes;

            nThisBytes =
                poItemObjectType->GetInstBytes( pabyData,
                                                nDataSize - nInstBytes );
            if (nThisBytes < 0 || nInstBytes > INT_MAX - nThisBytes)
            {
                CPLError(CE_Failure, CPLE_AppDefined, "Invalid return value");
                return -1;
            }

            nInstBytes += nThisBytes;
            pabyData += nThisBytes;
        }
    }

    return( nInstBytes );
}
