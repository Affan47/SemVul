TI_buildStudyQuery(DcmDataset **query)
{
    if (*query != NULL) delete *query;
    *query = new DcmDataset;
    if (*query == NULL) {
        DCMQRDB_ERROR("Help, out of memory");
        return;
    }

    DU_putStringDOElement(*query, DCM_QueryRetrieveLevel, "STUDY");
    DU_putStringDOElement(*query, DCM_StudyInstanceUID, NULL);
    DU_putStringDOElement(*query, DCM_StudyID, NULL);
    DU_putStringDOElement(*query, DCM_PatientName, NULL);
    DU_putStringDOElement(*query, DCM_PatientID, NULL);
}
