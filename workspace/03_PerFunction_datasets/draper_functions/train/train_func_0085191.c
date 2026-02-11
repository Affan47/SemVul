thBufferWrite(
  Th_Interp *interp,
  Buffer *pBuffer,
  const char *zAdd,
  int nAdd
){
  int nReq;

  if( nAdd<0 ){
    nAdd = th_strlen(zAdd);
  }
  nReq = pBuffer->nBuf+nAdd+1;

  if( nReq>pBuffer->nBufAlloc ){
    char *zNew;
    int nNew;

    nNew = nReq*2;
    zNew = (char *)Th_Malloc(interp, nNew);
    memcpy(zNew, pBuffer->zBuf, pBuffer->nBuf);
    Th_Free(interp, pBuffer->zBuf);
    pBuffer->nBufAlloc = nNew;
    pBuffer->zBuf = zNew;
  }

  memcpy(&pBuffer->zBuf[pBuffer->nBuf], zAdd, nAdd);
  pBuffer->nBuf += nAdd;
  pBuffer->zBuf[pBuffer->nBuf] = '\0';

  return TH_OK;
}
