TI_buildSeriesQuery(DcmDataset **query, TI_StudyEntry *study)
{
    if (*query != NULL) delete *query;
    *query = new DcmDataset;
    if (*query == NULL) {
        DCMQRDB_ERROR("Help, out of memory");
        return;
    }

    DU_putStringDOElement(*query, DCM_QueryRetrieveLevel, "SERIES");
    DU_putStringDOElement(*query, DCM_StudyInstanceUID,
        study->studyInstanceUID);
    DU_putStringDOElement(*query, DCM_SeriesInstanceUID, NULL);
    DU_putStringDOElement(*query, DCM_Modality, NULL);
    DU_putStringDOElement(*query, DCM_SeriesNumber, NULL);
}
