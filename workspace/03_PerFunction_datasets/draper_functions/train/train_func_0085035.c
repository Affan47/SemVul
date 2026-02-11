load_file_data(
  const char * file_path,
  char ** data_ptr_ptr)
{
  FILE * file;
  long size;
  bool ret;
  char * data_ptr;

  ret = true;
  *data_ptr_ptr = NULL;

  file = fopen(file_path, "r");
  if (file == NULL)
  {
    log_error("Failed to open '%s' for reading", file_path);
    goto exit;
  }

  if (fseek(file, 0, SEEK_END) == -1)
  {
    log_error("fseek('%s') failed", file_path);
    goto exit_close;
  }

  size = ftell(file);
  if (size == -1)
  {
    log_error("ftell('%s') failed", file_path);
    goto exit_close;
  }

  data_ptr = malloc(size + 1);
  if (data_ptr == NULL)
  {
    log_error("Failed to allocate %ld bytes for data of file '%s'", size + 1, file_path);
    ret = false;
    goto exit_close;
  }

  if (fseek(file, 0, SEEK_SET) == -1)
  {
    log_error("fseek('%s') failed", file_path);
    goto exit_close;
  }

  if (fread(data_ptr, size, 1, file) != 1)
  {
    log_error("Failed to read %ld bytes of data from file '%s'", size, file_path);
    goto exit_free_data;
  }

  data_ptr[size] = 0;

  *data_ptr_ptr = data_ptr;
  goto exit_close;

exit_free_data:
  free(data_ptr);

exit_close:
  fclose(file);

exit:
  return ret;
}
