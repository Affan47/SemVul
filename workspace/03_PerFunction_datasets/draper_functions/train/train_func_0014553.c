vtkWrapHierarchy_ParseHeaderFile(
  FILE *fp, const char *filename, const char *module_name,
  const char *flags, char **lines)
{
  FileInfo *data;
  const char *header_file;
  size_t k, n;


  if (lines == NULL)
    {
    lines = (char **)malloc(sizeof(char *));
    lines[0] = NULL;
    }


  vtkParse_SetIgnoreBTX(1);


  data = vtkParse_ParseFile(filename, fp, stderr);

  if (!data)
    {
    free(lines);
    return 0;
    }


  n = 0;
  while (lines[n] != NULL)
    {
    n++;
    }

  k = strlen(data->FileName) - 1;
  while (k > 0 && data->FileName[k-1] != '/' && data->FileName[k-1] != '\\')
    {
    k--;
    }
  header_file = &data->FileName[k];


  lines = append_namespace_contents(
    lines, &n, data->Contents, data->MainClass, 0,
    header_file, module_name, flags);

  vtkParse_Free(data);

  return lines;
}
