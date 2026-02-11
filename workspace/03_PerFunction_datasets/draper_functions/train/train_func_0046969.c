LookupNodesCustomNonCompressedCase()
{
    unsigned int i;
    unsigned int j = 0;

    for(i = 0; i < nReqIds; i++)
    {
        GIntBig id = panReqIds[i];

        int nBucket = (int)(id / NODE_PER_BUCKET);
        int nOffInBucket = id % NODE_PER_BUCKET;
        int nOffInBucketReduced = nOffInBucket >> NODE_PER_SECTOR_SHIFT;
        int nOffInBucketReducedRemainer = nOffInBucket & ((1 << NODE_PER_SECTOR_SHIFT) - 1);

        int nBitmapIndex = nOffInBucketReduced / 8;
        int nBitmapRemainer = nOffInBucketReduced % 8;

        if( nBucket >= nBuckets )
        {
            CPLError(CE_Failure,  CPLE_AppDefined,
                    "Cannot read node " CPL_FRMT_GIB, id);
            continue;

        }
        Bucket* psBucket = &papsBuckets[nBucket];
        if( psBucket->u.pabyBitmap == NULL )
        {
            CPLError(CE_Failure,  CPLE_AppDefined,
                    "Cannot read node " CPL_FRMT_GIB, id);
            continue;

        }

        int k;
        int nSector = 0;
        for(k = 0; k < nBitmapIndex; k++)
            nSector += abyBitsCount[psBucket->u.pabyBitmap[k]];
        if (nBitmapRemainer)
            nSector += abyBitsCount[psBucket->u.pabyBitmap[nBitmapIndex] & ((1 << nBitmapRemainer) - 1)];

        VSIFSeekL(fpNodes, psBucket->nOff + nSector * SECTOR_SIZE + nOffInBucketReducedRemainer * sizeof(LonLat), SEEK_SET);
        if( VSIFReadL(pasLonLatArray + j, 1, sizeof(LonLat), fpNodes) != sizeof(LonLat) )
        {
            CPLError(CE_Failure,  CPLE_AppDefined,
                     "Cannot read node " CPL_FRMT_GIB, id);

        }
        else
        {
            panReqIds[j] = id;
            if( pasLonLatArray[j].nLon || pasLonLatArray[j].nLat )
                j++;
        }
    }
    nReqIds = j;
}
