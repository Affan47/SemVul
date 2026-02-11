InstallStreamFilter()
  {


    if(pInFormat && !(pInFormat->Flags() & (READBINARY | READXML)) && pInStream->rdbuf()!=pLineEndBuf)
    {
      delete pLineEndBuf;
      pLineEndBuf = NULL;
      pLineEndBuf = new LErdbuf(pInStream->rdbuf());
      pInStream->rdbuf(pLineEndBuf);
    }
  }
