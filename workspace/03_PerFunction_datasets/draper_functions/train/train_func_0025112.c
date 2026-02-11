sqliteOsRead(OsFile *id, void *pBuf, int amt){
#if OS_UNIX
  int got;
  SimulateIOError(SQLITE_IOERR);
  TIMER_START;
  got = read(id->fd, pBuf, amt);
  TIMER_END;
  TRACE4("READ    %-3d %7d %d\n", id->fd, last_page, elapse);
  SEEK(0);

  if( got==amt ){
    return SQLITE_OK;
  }else{
    return SQLITE_IOERR;
  }
#endif
#if OS_WIN
  DWORD got;
  SimulateIOError(SQLITE_IOERR);
  TRACE2("READ %d\n", last_page);
  if( !ReadFile(id->h, pBuf, amt, &got, 0) ){
    got = 0;
  }
  if( got==(DWORD)amt ){
    return SQLITE_OK;
  }else{
    return SQLITE_IOERR;
  }
#endif
#if OS_MAC
  int got;
  SimulateIOError(SQLITE_IOERR);
  TRACE2("READ %d\n", last_page);
# ifdef _LARGE_FILE
  FSReadFork(id->refNum, fsAtMark, 0, (ByteCount)amt, pBuf, (ByteCount*)&got);
# else
  got = amt;
  FSRead(id->refNum, &got, pBuf);
# endif
  if( got==amt ){
    return SQLITE_OK;
  }else{
    return SQLITE_IOERR;
  }
#endif
}
