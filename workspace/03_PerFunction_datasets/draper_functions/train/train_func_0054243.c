GetBlock( int nXOffset, int nYOffset, void * pData )

{
    DDFRecord   *poRecord = NULL;
    int         nBytesPerValue;
    int         iTry;

    CPLAssert( nXOffset == 0 );


    CPLAssert( EQUAL(szFMT,"BI16") || EQUAL(szFMT,"BFP32") );

    if( EQUAL(szFMT,"BI16") )
        nBytesPerValue = 2;
    else
        nBytesPerValue = 4;

    for(iTry=0;iTry<2;iTry++)
    {


        CPLErrorReset();
        while( (poRecord = oDDFModule.ReadRecord()) != NULL )
        {
            if( poRecord->GetIntSubfield( "CELL", 0, "ROWI", 0 )
                == nYOffset + nYStart )
            {
                break;
            }
        }

        if( CPLGetLastErrorType() == CE_Failure )
            return FALSE;


        if( poRecord == NULL )
        {
            if (iTry == 0)
                oDDFModule.Rewind();
            else
            {
                CPLError( CE_Failure, CPLE_AppDefined,
                          "Cannot read scanline %d.  Raster access failed.\n",
                          nYOffset );
                return FALSE;
            }
        }
        else
        {
            break;
        }
    }


    DDFField    *poCVLS;

    poCVLS = poRecord->FindField( "CVLS" );
    if( poCVLS == NULL )
        return FALSE;

    if( poCVLS->GetRepeatCount() != nXSize )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Cell record is %d long, but we expected %d, the number\n"
                  "of pixels in a scanline.  Raster access failed.\n",
                  poCVLS->GetRepeatCount(), nXSize );
        return FALSE;
    }


    if( poCVLS->GetDataSize() < nBytesPerValue * nXSize
        || poCVLS->GetDataSize() > nBytesPerValue * nXSize + 1 )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Cell record is not of expected format.  Raster access "
                  "failed.\n" );

        return FALSE;
    }


    memcpy( pData, poCVLS->GetData(), nXSize * nBytesPerValue );

#ifdef CPL_LSB
    if( nBytesPerValue == 2 )
    {
        for( int i = 0; i < nXSize; i++ )
        {
            ((GInt16 *) pData)[i] = CPL_MSBWORD16(((GInt16 *) pData)[i]);
        }
    }
    else
    {
        for( int i = 0; i < nXSize; i++ )
        {
            CPL_MSBPTR32( ((GByte *)pData) + i*4 );
        }
    }
#endif

    return TRUE;
}
