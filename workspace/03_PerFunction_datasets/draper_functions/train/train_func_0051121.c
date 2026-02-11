EXTRACTOR_common_unzip_go_find_local_file (struct EXTRACTOR_UnzipFile *file,
					   const char *szFileName,
					   int iCaseSensitivity)
{
  int err;


  struct EXTRACTOR_UnzipFileInfo cur_file_infoSaved;
  struct UnzipFileInfoInternal cur_file_info_internalSaved;
  uLong num_fileSaved;
  uLong pos_in_central_dirSaved;

  if (NULL == file)
    return EXTRACTOR_UNZIP_PARAMERROR;
  if (strlen (szFileName) >= UNZ_MAXFILENAMEINZIP)
    return EXTRACTOR_UNZIP_PARAMERROR;
  if (! file->current_file_ok)
    return EXTRACTOR_UNZIP_END_OF_LIST_OF_FILE;


  num_fileSaved = file->num_file;
  pos_in_central_dirSaved = file->pos_in_central_dir;
  cur_file_infoSaved = file->cur_file_info;
  cur_file_info_internalSaved = file->cur_file_info_internal;
  err = EXTRACTOR_common_unzip_go_to_first_file (file);

  while (EXTRACTOR_UNZIP_OK == err)
    {
      char szCurrentFileName[UNZ_MAXFILENAMEINZIP + 1];

      if (EXTRACTOR_UNZIP_OK !=
	  (err = EXTRACTOR_common_unzip_get_current_file_info (file, NULL,
							       szCurrentFileName,
							       sizeof (szCurrentFileName) - 1,
							       NULL, 0, NULL, 0)))
	break;
      if (0 ==
	  EXTRACTOR_common_unzip_string_file_name_compare (szCurrentFileName,
							   szFileName,
							   iCaseSensitivity))
	return EXTRACTOR_UNZIP_OK;
      err = EXTRACTOR_common_unzip_go_to_next_file (file);
    }


  file->num_file = num_fileSaved;
  file->pos_in_central_dir = pos_in_central_dirSaved;
  file->cur_file_info = cur_file_infoSaved;
  file->cur_file_info_internal = cur_file_info_internalSaved;
  return err;
}
