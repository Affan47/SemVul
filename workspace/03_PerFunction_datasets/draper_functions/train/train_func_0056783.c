DSDPMMalloc(const char* fname, size_t size, void** mmem){
  void*tt=0;
  DSDPFunctionBegin;
  if (size>0){
#ifdef DSDPMATLAB
    tt=(void*)mxMalloc(size);
#else
    tt=(void*)malloc(size);
#endif
    if (tt==NULL){
      *mmem=0;
      DSDPSETERR3(100,"Memory Error in routine '%s'. Cannot allocate %d bytes, %d MB\n",fname,size,(int)(size/1000000));
    }
    memset(tt,0,size);
    *mmem=tt;

    if (mmmem<DSDPMEMMAX){
      DSDPMemoryTable[mmmem].size=size;
      DSDPMemoryTable[mmmem].freed=0;
      strncpy(DSDPMemoryTable[mmmem].fname,fname,19);
      DSDPMemoryTable[mmmem].mem=tt;
    }
    mmmem++;

  } else {
    *mmem=0;
  }
  DSDPFunctionReturn(0);
}
