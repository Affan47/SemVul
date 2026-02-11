funcDCM_RescaleType(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  ARG_NOT_USED(image);
  ARG_NOT_USED(exception);

  if (strncmp((char *) dcm->data,"OD",2) == 0)
    dcm->rescale_type=DCM_RT_OPTICAL_DENSITY;
  else if (strncmp((char *) dcm->data,"HU",2) == 0)
    dcm->rescale_type=DCM_RT_HOUNSFIELD;
  else if (strncmp((char *) dcm->data,"US",2) == 0)
    dcm->rescale_type=DCM_RT_UNSPECIFIED;
  else
    dcm->rescale_type=DCM_RT_UNKNOWN;
  return MagickPass;
}
