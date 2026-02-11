vtkWrapHierarchy_TryParseHeaderFile(
  const char *file_name, const char *module_name,
  const char *flags, char **lines)
{
  FILE *input_file;

  input_file = fopen(file_name, "r");

  if (!input_file)
    {
    fprintf(stderr, "vtkWrapHierarchy: couldn't open file %s\n",
            file_name);
    exit(1);
    }

  lines = vtkWrapHierarchy_ParseHeaderFile(
                 input_file, file_name, module_name, flags, lines);

  if (!lines)
    {
    fclose(input_file);
    exit(1);
    }
  fclose(input_file);

  return lines;
}
