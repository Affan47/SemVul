LoadBlockInfo()

{
    int		iBlock;
    HFAEntry	*poDMS;

    if( panBlockFlag != NULL )
        return( CE_None );

    poDMS = poNode->GetNamedChild( "RasterDMS" );
    if( poDMS == NULL )
    {
        if( poNode->GetNamedChild( "ExternalRasterDMS" ) != NULL )
            return LoadExternalBlockInfo();

        CPLError( CE_Failure, CPLE_AppDefined,
               "Can't find RasterDMS field in Eimg_Layer with block list.\n");

        return CE_Failure;
    }

    panBlockStart = (vsi_l_offset *)VSIMalloc2(sizeof(vsi_l_offset), nBlocks);
    panBlockSize = (int *) VSIMalloc2(sizeof(int), nBlocks);
    panBlockFlag = (int *) VSIMalloc2(sizeof(int), nBlocks);

    if (panBlockStart == NULL || panBlockSize == NULL || panBlockFlag == NULL)
    {
        CPLError( CE_Failure, CPLE_OutOfMemory,
                 "HFABand::LoadBlockInfo : Out of memory\n");

        CPLFree(panBlockStart);
        CPLFree(panBlockSize);
        CPLFree(panBlockFlag);
        panBlockStart = NULL;
        panBlockSize = NULL;
        panBlockFlag = NULL;
        return CE_Failure;
    }

    for( iBlock = 0; iBlock < nBlocks; iBlock++ )
    {
        char	szVarName[64];
        int	nLogvalid, nCompressType;

        sprintf( szVarName, "blockinfo[%d].offset", iBlock );
        panBlockStart[iBlock] = (GUInt32)poDMS->GetIntField( szVarName );

        sprintf( szVarName, "blockinfo[%d].size", iBlock );
        panBlockSize[iBlock] = poDMS->GetIntField( szVarName );

        sprintf( szVarName, "blockinfo[%d].logvalid", iBlock );
        nLogvalid = poDMS->GetIntField( szVarName );

        sprintf( szVarName, "blockinfo[%d].compressionType", iBlock );
        nCompressType = poDMS->GetIntField( szVarName );

        panBlockFlag[iBlock] = 0;
        if( nLogvalid )
            panBlockFlag[iBlock] |= BFLG_VALID;
        if( nCompressType != 0 )
            panBlockFlag[iBlock] |= BFLG_COMPRESSED;
    }

    return( CE_None );
}
