buildSpectroscopyRecord(DcmDirectoryRecord *record,
                                                               DcmItem *dataset,
                                                               const OFString &referencedFileID,
                                                               const OFString &sourceFilename)
{

    if (record == NULL)
        record = new DcmDirectoryRecord(ERT_Spectroscopy, referencedFileID.c_str(), sourceFilename.c_str());
    if (record != NULL)
    {

        if (record->error().good())
        {

            copyElementType1(dataset, DCM_ImageType, record, sourceFilename);
            copyElementType1(dataset, DCM_ContentDate, record, sourceFilename);
            copyElementType1(dataset, DCM_ContentTime, record, sourceFilename);
            copyElementType1(dataset, DCM_InstanceNumber, record, sourceFilename);
            copyElementType1C(dataset, DCM_ReferencedImageEvidenceSequence, record, sourceFilename);
            copyElementType1(dataset, DCM_NumberOfFrames, record, sourceFilename);
            copyElementType1(dataset, DCM_Rows, record, sourceFilename);
            copyElementType1(dataset, DCM_Columns, record, sourceFilename);
            copyElementType1(dataset, DCM_DataPointRows, record, sourceFilename);
            copyElementType1(dataset, DCM_DataPointColumns, record, sourceFilename);


            if ((ApplicationProfile == AP_GeneralPurposeDVD) ||
                (ApplicationProfile == AP_USBandFlash))
            {
                copyElementType1(dataset, DCM_Rows, record, sourceFilename);
                copyElementType1(dataset, DCM_Columns, record, sourceFilename);
                copyElementType1C(dataset, DCM_FrameOfReferenceUID, record, sourceFilename);
                copyElementType1C(dataset, DCM_SynchronizationFrameOfReferenceUID, record, sourceFilename);
                copyElementType1C(dataset, DCM_NumberOfFrames, record, sourceFilename);
                copyElementType1C(dataset, DCM_AcquisitionTimeSynchronized, record, sourceFilename);
                copyElementType1C(dataset, DCM_AcquisitionDateTime, record, sourceFilename);

                copyElementType1C(dataset, DCM_ReferencedImageSequence, record, sourceFilename);
                copyElementType1C(dataset, DCM_ImagePositionPatient, record, sourceFilename);
                copyElementType1C(dataset, DCM_ImageOrientationPatient, record, sourceFilename);
                copyElementType1C(dataset, DCM_PixelSpacing, record, sourceFilename);
            }
        } else {
            printRecordErrorMessage(record->error(), ERT_Spectroscopy, "create");

            delete record;
            record = NULL;
        }
    } else
        printRecordErrorMessage(EC_MemoryExhausted, ERT_Spectroscopy, "create");
    return record;
}
