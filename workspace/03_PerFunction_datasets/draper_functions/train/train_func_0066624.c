isTopDirectory(const FXString& file){
#ifndef WIN32
  return ISPATHSEP(file[0]) && file[1]=='\0';
#else
  return (ISPATHSEP(file[0]) && (file[1]=='\0' || (ISPATHSEP(file[1]) && file[2]=='\0'))) || (Ascii::isLetter(file[0]) && file[1]==':' && (file[2]=='\0' || (ISPATHSEP(file[2]) && file[3]=='\0')));
#endif
  }
