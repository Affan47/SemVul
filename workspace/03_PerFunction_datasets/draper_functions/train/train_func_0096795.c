createDataDict()
{

#ifdef WITH_THREADS
  dataDictLock.wrlock();
#endif
#ifdef DONT_LOAD_EXTERNAL_DICTIONARIES
  const OFBool loadExternal = OFFalse;
#else
  const OFBool loadExternal = OFTrue;
#endif


  if (!dataDict)
    dataDict = new DcmDataDictionary(OFTrue , loadExternal);
#ifdef WITH_THREADS
  dataDictLock.unlock();
#endif
}
