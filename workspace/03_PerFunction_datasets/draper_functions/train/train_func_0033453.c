size(){
  if(isOpen()){
#ifdef WIN32
    ULARGE_INTEGER result;
    result.LowPart=::GetFileSize(device,&result.HighPart);
    return result.QuadPart;
#else
    struct stat data;
    if(::fstat(device,&data)==0) return data.st_size;
#endif
    }
  return -1;
  }
