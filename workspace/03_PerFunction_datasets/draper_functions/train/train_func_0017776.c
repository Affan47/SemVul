close(){
  if(isOpen()){
    FXInputHandle dev=device;
    device=BadHandle;
#ifdef WIN32
    return ::CloseHandle(dev)!=0;
#else
    return ::close(dev)==0;
#endif
    }
  return false;
  }
