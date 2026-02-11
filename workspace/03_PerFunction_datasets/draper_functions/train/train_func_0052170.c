kwsysProcess_SetWorkingDirectory(kwsysProcess* cp, const char* dir)
{
  if(!cp)
    {
    return 0;
    }
  if(cp->WorkingDirectory == dir)
    {
    return 1;
    }
  if(cp->WorkingDirectory && dir && strcmp(cp->WorkingDirectory, dir) == 0)
    {
    return 1;
    }
  if(cp->WorkingDirectory)
    {
    free(cp->WorkingDirectory);
    cp->WorkingDirectory = 0;
    }
  if(dir)
    {
    cp->WorkingDirectory = (char*)malloc(strlen(dir) + 1);
    if(!cp->WorkingDirectory)
      {
      return 0;
      }
    strcpy(cp->WorkingDirectory, dir);
    }
  return 1;
}
