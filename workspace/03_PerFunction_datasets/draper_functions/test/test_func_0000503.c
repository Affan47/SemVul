FilesDiffer(const char* source,
                              const char* destination)
{
  struct stat statSource;
  if (stat(source, &statSource) != 0)
    {
    return true;
    }

  struct stat statDestination;
  if (stat(destination, &statDestination) != 0)
    {
    return true;
    }

  if(statSource.st_size != statDestination.st_size)
    {
    return true;
    }

  if(statSource.st_size == 0)
    {
    return false;
    }

#if defined(_WIN32) || defined(__CYGWIN__)
  kwsys_ios::ifstream finSource(source, (kwsys_ios::ios::binary |
                                         kwsys_ios::ios::in));
  kwsys_ios::ifstream finDestination(destination, (kwsys_ios::ios::binary |
                                                   kwsys_ios::ios::in));
#else
  kwsys_ios::ifstream finSource(source);
  kwsys_ios::ifstream finDestination(destination);
#endif
  if(!finSource || !finDestination)
    {
    return true;
    }


  char source_buf[KWSYS_ST_BUFFER];
  char dest_buf[KWSYS_ST_BUFFER];
  off_t nleft = statSource.st_size;
  while(nleft > 0)
    {

    kwsys_ios::streamsize nnext = (nleft > KWSYS_ST_BUFFER)? KWSYS_ST_BUFFER : static_cast<kwsys_ios::streamsize>(nleft);
    finSource.read(source_buf, nnext);
    finDestination.read(dest_buf, nnext);


    if(static_cast<kwsys_ios::streamsize>(finSource.gcount()) != nnext ||
       static_cast<kwsys_ios::streamsize>(finDestination.gcount()) != nnext)
      {
      return true;
      }


    if(memcmp(static_cast<const void*>(source_buf),
              static_cast<const void*>(dest_buf),
              static_cast<size_t>(nnext)) != 0)
      {
      return true;
      }


    nleft -= nnext;
    }


  return false;
}
