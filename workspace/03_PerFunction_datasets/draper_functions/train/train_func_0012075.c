sqliteOsClose(OsFile *id){
#if OS_UNIX
  sqliteOsUnlock(id);
  if( id->dirfd>=0 ) close(id->dirfd);
  id->dirfd = -1;
  sqliteOsEnterMutex();
  if( id->pOpen->nLock ){


    int *aNew;
    struct openCnt *pOpen = id->pOpen;
    pOpen->nPending++;
    aNew = sqliteRealloc( pOpen->aPending, pOpen->nPending*sizeof(int) );
    if( aNew==0 ){

    }else{
      pOpen->aPending = aNew;
      pOpen->aPending[pOpen->nPending-1] = id->fd;
    }
  }else{

    close(id->fd);
  }
  releaseLockInfo(id->pLock);
  releaseOpenCnt(id->pOpen);
  sqliteOsLeaveMutex();
  TRACE2("CLOSE   %-3d\n", id->fd);
  OpenCounter(-1);
  return SQLITE_OK;
#endif
#if OS_WIN
  CloseHandle(id->h);
  OpenCounter(-1);
  return SQLITE_OK;
#endif
#if OS_MAC
  if( id->refNumRF!=-1 )
    FSClose(id->refNumRF);
# ifdef _LARGE_FILE
  FSCloseFork(id->refNum);
# else
  FSClose(id->refNum);
# endif
  if( id->delOnClose ){
    unlink(id->pathToDel);
    sqliteFree(id->pathToDel);
  }
  OpenCounter(-1);
  return SQLITE_OK;
#endif
}
