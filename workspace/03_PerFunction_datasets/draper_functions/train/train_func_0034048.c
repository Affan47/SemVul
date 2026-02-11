buildHangingProtocolRecord(DcmDirectoryRecord *record,
                                                                  DcmFileFormat *fileformat,
                                                                  const OFString &referencedFileID,
                                                                  const OFString &sourceFilename)
{

    if (record == NULL)
        record = new DcmDirectoryRecord(ERT_HangingProtocol, referencedFileID.c_str(), sourceFilename.c_str(), fileformat);
    if (record != NULL)
    {

        if (record->error().good())
        {
            DcmDataset *dataset = fileformat->getDataset();
            copyElementType1(dataset, DCM_HangingProtocolName, record, sourceFilename);
            copyElementType1(dataset, DCM_HangingProtocolDescription, record, sourceFilename);
            copyElementType1(dataset, DCM_HangingProtocolLevel, record, sourceFilename);
            copyElementType1(dataset, DCM_HangingProtocolCreator, record, sourceFilename);
            copyElementType1(dataset, DCM_HangingProtocolCreationDateTime, record, sourceFilename);

            copyElementType1(dataset, DCM_HangingProtocolDefinitionSequence, record, sourceFilename);
            copyElementType1(dataset, DCM_NumberOfPriorsReferenced, record, sourceFilename);
            copyElementType2(dataset, DCM_HangingProtocolUserIdentificationCodeSequence, record, sourceFilename);
        } else {
            printRecordErrorMessage(record->error(), ERT_HangingProtocol, "create");

            delete record;
            record = NULL;
        }
    } else
        DCMDATA_ERROR("out of memory (creating patient record)");
    return record;
}
