mailmh_folder_get_message_size(struct mailmh_folder * folder,
				   uint32_t indx, size_t * result)
{
  int r;
  char * filename;
  struct stat buf;

  r = mailmh_folder_get_message_filename(folder, indx, &filename);
  if (r != MAILMH_NO_ERROR)
    return r;

  r = stat(filename, &buf);
  free(filename);
  if (r < 0)
    return MAILMH_ERROR_FILE;

  * result = buf.st_size;

  return MAILMH_NO_ERROR;
}
