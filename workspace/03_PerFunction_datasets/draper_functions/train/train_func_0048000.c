filename_is_used (GList *files, const char *filename)
{
  ComputerFile *file;

  while (files != NULL)
    {
      file = files->data;

      if (file->filename == NULL)
        return FALSE;

      if (strcmp (file->filename, filename) == 0)
        return TRUE;

      files = files->next;
    }
  return FALSE;
}
