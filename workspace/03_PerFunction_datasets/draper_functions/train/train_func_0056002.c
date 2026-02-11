buildPaletteRecord(DcmDirectoryRecord *record,
                                                          DcmItem *dataset,
                                                          const OFString &referencedFileID,
                                                          const OFString &sourceFilename)
{

    if (record == NULL)
        record = new DcmDirectoryRecord(ERT_Palette, referencedFileID.c_str(), sourceFilename.c_str());
    if (record != NULL)
    {

        if (record->error().good())
        {

            copyElementType1(dataset, DCM_ContentLabel, record, sourceFilename);
            copyElementType2(dataset, DCM_ContentDescription, record, sourceFilename);
        } else {
            printRecordErrorMessage(record->error(), ERT_Palette, "create");

            delete record;
            record = NULL;
        }
    } else
        printRecordErrorMessage(EC_MemoryExhausted, ERT_Palette, "create");
    return record;
}
