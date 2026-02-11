find_file_nocase(const char * dir, const char * file)
  {
  DIR * d;
  struct dirent * res;
  char * ret;
  d = opendir(dir);

  while( (res=readdir(d)) )
    {
    if(!res)
      break;


    if(!strcasecmp(res->d_name, file))
      {
      ret = bgav_sprintf("%s/%s", dir, res->d_name);
      closedir(d);
      return ret;
      }
    }
  closedir(d);
  return NULL;
  }
