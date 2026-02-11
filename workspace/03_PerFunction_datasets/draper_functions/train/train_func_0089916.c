buildSeriesRecord(DcmDirectoryRecord *record,
                                                         DcmFileFormat *fileformat,
                                                         const OFFilename &sourceFilename)
{

    if (record == NULL)
        record = new DcmDirectoryRecord(ERT_Series, NULL, sourceFilename, fileformat);
    if (record != NULL)
    {

        if (record->error().good())
        {
            DcmDataset *dataset = fileformat->getDataset();

            copyElementType1(dataset, DCM_Modality, record, sourceFilename);
            copyElementType1(dataset, DCM_SeriesInstanceUID, record, sourceFilename);

            copyElementType1C(dataset, DCM_SeriesNumber, record, sourceFilename);
            if ((ApplicationProfile == AP_GeneralPurposeDVDJPEG) ||
                (ApplicationProfile == AP_GeneralPurposeDVDJPEG2000) ||
                (ApplicationProfile == AP_GeneralPurposeBDJPEG) ||
                (ApplicationProfile == AP_GeneralPurposeBDJPEG2000) ||
                (ApplicationProfile == AP_GeneralPurposeBDMPEG2MPatML) ||
                (ApplicationProfile == AP_GeneralPurposeBDMPEG2MPatHL) ||
                (ApplicationProfile == AP_GeneralPurposeBDMPEG4HPatLV41) ||
                (ApplicationProfile == AP_GeneralPurposeBDMPEG4HPatLV41BD) ||
                (ApplicationProfile == AP_USBandFlashJPEG) ||
                (ApplicationProfile == AP_USBandFlashJPEG2000) ||
                (ApplicationProfile == AP_MPEG2MPatMLDVD))
            {

                copyElementType1C(dataset, DCM_InstitutionName, record, sourceFilename);
                copyElementType1C(dataset, DCM_InstitutionAddress, record, sourceFilename);
                copyElementType1C(dataset, DCM_PerformingPhysicianName, record, sourceFilename);
            }
            else if ((ApplicationProfile == AP_BasicCardiac) ||
                     (ApplicationProfile == AP_XrayAngiographic) ||
                     (ApplicationProfile == AP_XrayAngiographicDVD))
            {

                copyStringWithDefault(dataset, DCM_InstitutionName, record, sourceFilename);
                copyStringWithDefault(dataset, DCM_InstitutionAddress, record, sourceFilename);
                copyStringWithDefault(dataset, DCM_PerformingPhysicianName, record, sourceFilename);
            }
        } else {
            printRecordErrorMessage(record->error(), ERT_Series, "create");

            delete record;
            record = NULL;
        }
    } else
        DCMDATA_ERROR("out of memory (creating series record)");
    return record;
}
