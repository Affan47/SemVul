ScanJPEGBlocks()

{
    int iBlock;
    GUIntBig nJPEGStart =
        psFile->pasSegmentInfo[psImage->iSegment].nSegmentStart;

    nQLevel = ScanJPEGQLevel( &nJPEGStart );


    panJPEGBlockOffset = (GIntBig *)
        VSICalloc(sizeof(GIntBig),
                  psImage->nBlocksPerRow*psImage->nBlocksPerColumn);
    if (panJPEGBlockOffset == NULL)
    {
        CPLError( CE_Failure, CPLE_OutOfMemory, "Out of memory");
        return CE_Failure;
    }
    panJPEGBlockOffset[0] = nJPEGStart;

    if ( psImage->nBlocksPerRow * psImage->nBlocksPerColumn == 1)
        return CE_None;

    for( iBlock = psImage->nBlocksPerRow * psImage->nBlocksPerColumn - 1;
         iBlock > 0; iBlock-- )
        panJPEGBlockOffset[iBlock] = -1;


    int iNextBlock = 1;
    GIntBig iSegOffset = 2;
    GIntBig iSegSize = psFile->pasSegmentInfo[psImage->iSegment].nSegmentSize
        - (nJPEGStart - psFile->pasSegmentInfo[psImage->iSegment].nSegmentStart);
    GByte abyBlock[512];
    int ignoreBytes = 0;

    while( iSegOffset < iSegSize-1 )
    {
        size_t nReadSize = MIN((size_t)sizeof(abyBlock),(size_t)(iSegSize - iSegOffset));
        size_t i;

        if( VSIFSeekL( psFile->fp, panJPEGBlockOffset[0] + iSegOffset,
                       SEEK_SET ) != 0 )
        {
            CPLError( CE_Failure, CPLE_FileIO,
                      "Seek error to jpeg data stream." );
            return CE_Failure;
        }

        if( VSIFReadL( abyBlock, 1, nReadSize, psFile->fp ) < (size_t)nReadSize)
        {
            CPLError( CE_Failure, CPLE_FileIO,
                      "Read error to jpeg data stream." );
            return CE_Failure;
        }

        for( i = 0; i < nReadSize-1; i++ )
        {
            if (ignoreBytes == 0)
            {
                if( abyBlock[i] == 0xff )
                {

                    if ( abyBlock[i+1] == 0xd8 )
                    {
                        panJPEGBlockOffset[iNextBlock++]
                             = panJPEGBlockOffset[0] + iSegOffset + i;

                        if( iNextBlock == psImage->nBlocksPerRow*psImage->nBlocksPerColumn)
                        {
                            return CE_None;
                        }
                    }


                    else if ( abyBlock[i+1] >= 0xe0 && abyBlock[i+1] < 0xf0 )
                    {
                        ignoreBytes = -2;
                    }
                }
            }
            else if (ignoreBytes < 0)
            {
                if (ignoreBytes == -1)
                {

                    ignoreBytes = abyBlock[i]*256 + abyBlock[i+1];
                }
                else
                    ignoreBytes++;
            }
            else
            {
                ignoreBytes--;
            }
        }

        iSegOffset += nReadSize - 1;
    }

    return CE_None;
}
