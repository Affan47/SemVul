InitializeTextMetadata()

{
    if( oSpecialMD.GetMetadata( "TEXT" ) != NULL )
        return;

    int iSegment;
    int iText = 0;


    for( iSegment = 0; iSegment < psFile->nSegmentCount; iSegment++ )
    {
        NITFSegmentInfo *psSegment = psFile->pasSegmentInfo + iSegment;

        if( !EQUAL(psSegment->szSegmentType,"TX") )
            continue;


        char *pabyHeaderData = (char *) CPLCalloc(1,
                (size_t) psSegment->nSegmentHeaderSize + 1);
        if (VSIFSeekL(psFile->fp, psSegment->nSegmentHeaderStart,
                      SEEK_SET) != 0 ||
            VSIFReadL(pabyHeaderData, 1, (size_t) psSegment->nSegmentHeaderSize,
                      psFile->fp) != psSegment->nSegmentHeaderSize)
        {
            CPLError( CE_Warning, CPLE_FileIO,
                      "Failed to read %d bytes of text header data at " CPL_FRMT_GUIB ".",
                      psSegment->nSegmentHeaderSize,
                      psSegment->nSegmentHeaderStart);
            CPLFree(pabyHeaderData);
            return;
        }

        oSpecialMD.SetMetadataItem( CPLString().Printf("HEADER_%d", iText),
                                    pabyHeaderData, "TEXT");
        CPLFree(pabyHeaderData);


        char *pabyTextData;


        pabyTextData = (char *) VSICalloc(1,(size_t)psSegment->nSegmentSize+1);
        if (pabyTextData == NULL)
        {
            CPLError( CE_Failure, CPLE_OutOfMemory, "Out of memory");
            return;
        }
        if( VSIFSeekL( psFile->fp, psSegment->nSegmentStart,
                       SEEK_SET ) != 0
            || VSIFReadL( pabyTextData, 1, (size_t)psSegment->nSegmentSize,
                          psFile->fp ) != psSegment->nSegmentSize )
        {
            CPLError( CE_Warning, CPLE_FileIO,
                      "Failed to read " CPL_FRMT_GUIB " bytes of text data at " CPL_FRMT_GUIB ".",
                      psSegment->nSegmentSize,
                      psSegment->nSegmentStart );
            CPLFree( pabyTextData );
            return;
        }

        oSpecialMD.SetMetadataItem( CPLString().Printf( "DATA_%d", iText),
                                    pabyTextData, "TEXT" );
        CPLFree( pabyTextData );

        iText++;
    }
}
