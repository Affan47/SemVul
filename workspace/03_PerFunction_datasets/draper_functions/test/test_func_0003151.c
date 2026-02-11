buildStereometricRecord(DcmDirectoryRecord *record,
                                                               DcmItem *  ,
                                                               const OFString &referencedFileID,
                                                               const OFString &sourceFilename)
{

    if (record == NULL)
        record = new DcmDirectoryRecord(ERT_Stereometric, referencedFileID.c_str(), sourceFilename.c_str());
    if (record != NULL)
    {

        if (record->error().good())
        {

        } else {
            printRecordErrorMessage(record->error(), ERT_Stereometric, "create");

            delete record;
            record = NULL;
        }
    } else
        printRecordErrorMessage(EC_MemoryExhausted, ERT_Stereometric, "create");
    return record;
}
