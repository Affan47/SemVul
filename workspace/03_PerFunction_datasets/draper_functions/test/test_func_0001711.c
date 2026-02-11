buildStructReportRecord(DcmDirectoryRecord *record,
                                                               DcmFileFormat *fileformat,
                                                               const OFString &referencedFileID,
                                                               const OFString &sourceFilename)
{

    if (record == NULL)
        record = new DcmDirectoryRecord(ERT_SRDocument, referencedFileID.c_str(), sourceFilename.c_str(), fileformat);
    if (record != NULL)
    {

        if (record->error().good())
        {
            DcmDataset *dataset = fileformat->getDataset();
            OFString tmpString;

            copyElementType1(dataset, DCM_InstanceNumber, record, sourceFilename);
            copyElementType1(dataset, DCM_CompletionFlag, record, sourceFilename);
            copyElementType1(dataset, DCM_VerificationFlag, record, sourceFilename);
            copyElementType1(dataset, DCM_ContentDate, record, sourceFilename);
            copyElementType1(dataset, DCM_ContentTime, record, sourceFilename);
            if (compare(getStringFromDataset(dataset, DCM_VerificationFlag, tmpString), "VERIFIED"))
            {


                DcmItem *ditem = NULL;
                OFCondition status = dataset->findAndGetSequenceItem(DCM_VerifyingObserverSequence, ditem, -1 );
                if (status.good())
                    copyElementType1(ditem, DCM_VerificationDateTime, record, sourceFilename);
                else
                    printAttributeErrorMessage(DCM_VerifyingObserverSequence, status, "retrieve");
            }
            copyElementType1(dataset, DCM_ConceptNameCodeSequence, record, sourceFilename);
            addConceptModContentItems(record, dataset);
        } else {
            printRecordErrorMessage(record->error(), ERT_SRDocument, "create");

            delete record;
            record = NULL;
        }
    } else
        printRecordErrorMessage(EC_MemoryExhausted, ERT_SRDocument, "create");
    return record;
}
