closeUnixFile(unqlite_file *id){
  unixFile *pFile = (unixFile*)id;
  if( pFile ){
    if( pFile->dirfd>=0 ){
      int err = close(pFile->dirfd);
      if( err ){
        pFile->lastErrno = errno;
        return UNQLITE_IOERR;
      }else{
        pFile->dirfd=-1;
      }
    }
    if( pFile->h>=0 ){
      int err = close(pFile->h);
      if( err ){
        pFile->lastErrno = errno;
        return UNQLITE_IOERR;
      }
    }
    unqlite_free(pFile->pUnused);
    SyZero(pFile,sizeof(unixFile));
  }
  return UNQLITE_OK;
}
