convertAllPointer( DcmDataset &dset,
                                            Uint32 beginOfDataSet,
                                            E_TransferSyntax oxfer,
                                            E_EncodingType enctype )
{
    OFCondition l_error = EC_Normal;
    DcmObject *obj = NULL;
    DcmDirectoryRecord *rec = NULL;
    DcmSequenceOfItems &localDirRecSeq = getDirRecSeq( dset );
    Uint32 offs_Item1 =  beginOfDataSet + lengthUntilSQ( dset, oxfer, enctype );
    unsigned long num = localDirRecSeq.card();

    Uint32 item_pos = offs_Item1;
    for (unsigned long i = 0; i < num; i++ )
    {
        obj = localDirRecSeq.nextInContainer(obj);
        rec = OFstatic_cast(DcmDirectoryRecord *, obj);
        rec->setFileOffset( item_pos );
        item_pos = lengthOfRecord( rec, oxfer, enctype ) + item_pos;
    }


    OFCondition e1 = convertGivenPointer( &dset, DCM_OffsetOfTheFirstDirectoryRecordOfTheRootDirectoryEntity );
    OFCondition e2 = convertGivenPointer( &dset, DCM_OffsetOfTheLastDirectoryRecordOfTheRootDirectoryEntity );

    OFCondition e3 = convertGivenPointer( &localDirRecSeq, DCM_OffsetOfTheNextDirectoryRecord );
    OFCondition e4 = convertGivenPointer( &localDirRecSeq, DCM_OffsetOfReferencedLowerLevelDirectoryEntity );
    OFCondition e5 = convertGivenPointer( &localDirRecSeq, DCM_RETIRED_MRDRDirectoryRecordOffset );

    if ( e1 == EC_InvalidVR || e2 == EC_InvalidVR || e3 == EC_InvalidVR || e4 == EC_InvalidVR || e5 == EC_InvalidVR )
        l_error = EC_InvalidVR;

    return l_error;
}
