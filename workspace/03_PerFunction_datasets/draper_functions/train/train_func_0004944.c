utlFileGetExt(const char *file_name)
{
  int len = strlen(file_name);


  int offset = len - 1;
  while (offset != 0)
  {

    if (file_name[offset] == '\\' || file_name[offset] == '/')
      return NULL;

    if (file_name[offset] == '.')
    {
      offset++;
      break;
    }

    offset--;
  }


  if (offset == 0)
    return NULL;

  int ext_size = len - offset + 1;
  char* file_ext = (char*)malloc(ext_size);

  for (int i = 0; i < ext_size-1; i++)
    file_ext[i] = (char)tolower(file_name[i+offset]);
  file_ext[ext_size-1] = 0;

  return file_ext;
}
