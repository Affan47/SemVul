amdmsGetColumnIndex(amdmsFITS *file, char *name, int *index)
{
  int status = 0;

  *index = -1;
  if (fits_get_colnum(file->fits, CASEINSEN, name, index, &status) != 0) {
    amdmsDebug(__FILE__, __LINE__,
	      "amdmsGetColumnIndex(%s, %s, ..) -> column not found!",
	      file->fileName, name);
    if (status != COL_NOT_FOUND) {
      amdmsReportFitsError(file, status,__LINE__, NULL);
    }
    return amdmsFALSE;
  }
  amdmsDebug(__FILE__, __LINE__, "amdmsGetColumnIndex(%s, ..) -> %d", name, *index);
  return amdmsTRUE;
}
