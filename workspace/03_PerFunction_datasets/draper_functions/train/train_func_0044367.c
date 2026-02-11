unixClose(unqlite_file *id){
  int rc = UNQLITE_OK;
  if( id ){
    unixFile *pFile = (unixFile *)id;
    unixUnlock(id, NO_LOCK);
    unixEnterMutex();
    if( pFile->pInode && pFile->pInode->nLock ){


      setPendingFd(pFile);
    }
    releaseInodeInfo(pFile);
    rc = closeUnixFile(id);
    unixLeaveMutex();
  }
  return rc;
}
