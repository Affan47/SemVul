send(const A &msg_)
{
  ipcWarn(wrnlvl(),"%t pA_Connection::send\n");
  if(isInReset()||readChannel()==0) return -1;

  MSBuffer *sb=createBufferFromAobj(msg_);
  if(NULL==sb) return -1;
  sendTheBuffer(sb);
  if (MSFalse==isWritePause()) writeChannel()->enable();
  return doWrite(MSFalse);
}
