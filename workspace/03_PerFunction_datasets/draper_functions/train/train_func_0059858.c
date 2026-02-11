NewExtension(string &src,char *ext)
  {
    string::size_type pos = (unsigned int)src.find_last_of(".");
    string dst;

    if (pos != string::npos)
      dst = src.substr(0,pos+1);
    else
      {
        dst = src;
        dst += ".";
      }

    dst += ext;
    return(dst);
  }
