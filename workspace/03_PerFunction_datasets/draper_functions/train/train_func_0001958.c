closeAccessor(string inName){
  if(gMutex){
    gMutex->lock();
  }
  CContent::iterator lFound=mContent.find(inName);

  cout << __FILE__ << ":" << __LINE__
       << "PID:" << getpid()
       << "OpenCloseCounter["
       << inName
       << "]"
       << (mContent[inName].mOpenCloseCounter) << endl;


#ifdef __GIFT_FREE_UNUSED_ACCESSORS
  if((lFound!=mContent.end())
     &&
     !(--(mContent[inName].mOpenCloseCounter))){
    delete lFound->second.mAccessor;
    mContent.erase(lFound);

    mFactoryContainer.closeAccessor(inName);
  }
#endif
  if(gMutex){
    gMutex->unlock();
  }
}
