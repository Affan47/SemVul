closePendingFds(unixFile *pFile){
  int rc = UNQLITE_OK;
  unixInodeInfo *pInode = pFile->pInode;
  UnixUnusedFd *pError = 0;
  UnixUnusedFd *p;
  UnixUnusedFd *pNext;
  for(p=pInode->pUnused; p; p=pNext){
    pNext = p->pNext;
    if( close(p->fd) ){
      pFile->lastErrno = errno;
	  rc = UNQLITE_IOERR;
      p->pNext = pError;
      pError = p;
    }else{
      unqlite_free(p);
    }
  }
  pInode->pUnused = pError;
  return rc;
}
