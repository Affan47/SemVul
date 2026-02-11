load_config(void)
{
  char *filename, *tmp;

  clear();

  tmp = getenv("HOME");
  if (tmp)
    {
      filename = new char[strlen(tmp) + 8];
      strcpy(filename, tmp);
      strcat(filename, "/.debug");
      load_file(filename);
      delete[] filename;
    }
}
