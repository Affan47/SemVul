amdmsReadKeywordDouble(amdmsFITS *file, char *name, double *value, char *comment)
{
  int status = 0;

  if (file == NULL) {
    return amdmsFALSE;
  }
  if (file->currStateFile != amdmsFILE_OPENED_STATE) {
    amdmsError(__FILE__, __LINE__,
	      "amdmsReadKeywordDouble(%s, %S, .., ..), no open file!", file->fileName, name);
    return amdmsFALSE;
  }
  if (fits_read_key_dbl(file->fits, name, value, comment, &status) != 0) {
    if (status != VALUE_UNDEFINED && status != KEY_NO_EXIST) {
      amdmsReportFitsError(file, status, __LINE__, name);
    }
    amdmsDebug(__FILE__, __LINE__,
	      "amdmsReadKeywordDouble(%s, %S, .., ..): keyword not found", file->fileName, name);
    return amdmsFALSE;
  }
  amdmsDebug(__FILE__, __LINE__,
	     "amdmsReadKeywordDouble(%s, %s, .., ..) = %f", file->fileName, name, *value);
  return amdmsTRUE;
}
