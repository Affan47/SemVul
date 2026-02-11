fsafeopen(const char *path, const char *mode)
{
  char newpath[MAX_PATH];
  int i, ret;


  ret = fsafetranslate(path, newpath);


  if(ret < -1)
    return NULL;


  if(ret == -1)
  {

    for(i = 0; i < (int)strlen(mode); i++)
    {
      if(mode[i] == 'r' || mode[i] == '+')
        return NULL;
    }


    strcpy(newpath, path);
  }


  return fopen(newpath, mode);
}
