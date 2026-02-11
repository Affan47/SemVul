edflib_is_file_used(const char *path)
{
  int i, file_used=0;

  for(i=0; i<EDFLIB_MAXFILES; i++)
  {
    if(hdrlist[i]!=NULL)
    {
      if(!(strcmp(path, hdrlist[i]->path)))
      {
        file_used = 1;

        break;
      }
    }
  }

  return(file_used);
}
