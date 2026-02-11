get_slice_info(const gchar * filename) {

  OFCondition result;
  DcmFileFormat dcm_format;
  DcmDataset * dcm_dataset;
  const char * return_str=NULL;
  slice_info_t * info=NULL;
  Sint32 return_sint32;

  result = dcm_format.loadFile(filename);
  if (result.bad()) return NULL;

  dcm_dataset = dcm_format.getDataset();
  if (dcm_dataset == NULL) return NULL;

  info = slice_info_new();
  info->filename = g_strdup(filename);

  dcm_dataset->findAndGetString(DCM_SeriesInstanceUID, return_str, OFTrue);
  if (return_str != NULL)
      info->series_instance_uid = g_strdup(return_str);

  dcm_dataset->findAndGetString(DCM_Modality, return_str, OFTrue);
  if (return_str != NULL)
      info->modality = g_strdup(return_str);

  dcm_dataset->findAndGetString(DCM_SeriesDescription, return_str, OFTrue);
  if (return_str != NULL)
      info->series_description = g_strdup(return_str);

  dcm_dataset->findAndGetString(DCM_PatientID, return_str, OFTrue);
  if (return_str != NULL)
      info->patient_id = g_strdup(return_str);

  dcm_dataset->findAndGetString(DCM_PatientName, return_str, OFTrue);
  if (return_str != NULL)
      info->patient_name = g_strdup(return_str);

  if (dcm_dataset->findAndGetSint32(DCM_SeriesNumber, return_sint32).good())
    info->series_number = return_sint32;

  return info;
}
