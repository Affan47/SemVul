prepareWrite (EndPoint endp,
                  Buffer *buffers,
                  EndpRWCB progress,
                  EndpRWCB done,
                  void *clientData)
{
  int bufferSizeTotal = 0 ;
  int idx ;

  ASSERT (endp != NULL) ;

  if (endp->outBuffer != NULL || FD_ISSET (endp->myFd,&wrSet))
    return 0 ;

  for (idx = 0 ; buffers != NULL && buffers [idx] != NULL ; idx++)
    bufferSizeTotal += bufferDataSize (buffers [idx]) ;

  endp->outBuffer = buffers ;
  endp->outBufferIdx = 0 ;
  endp->outIndex = 0 ;
  endp->outProgressCbk = progress ;
  endp->outDoneCbk = done ;
  endp->outClientData = clientData ;
  endp->outSize = bufferSizeTotal ;
  endp->outAmtWritten = 0 ;

  FD_SET (endp->myFd, &wrSet) ;
  FD_SET (endp->myFd, &exSet) ;

  return 1 ;
}
