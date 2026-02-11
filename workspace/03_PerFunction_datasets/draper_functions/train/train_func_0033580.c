ipcSetDebug(I handle_,I val_)
{
  InitializeIfNeeded();

  if (0==handle_) ipcWarnFlag=val_;
  else
  {
    AipcService *srvptr=lookupAnyHandle(handle_);
    if(!srvptr)return -1;
    if(val_)srvptr->turnDebugOn();else srvptr->turnDebugOff();
    if (-1==ipcWarnFlag) ipcWarnFlag=0;
  }
  if (ipcWarnFlag>=0)
  {
    SetWarnFunc(WarnFunc);
    MSMessageLog::quietMode(MSFalse);
  } else {
    SetWarnFunc(0);
    MSMessageLog::quietMode(MSTrue);
  }
  return val_;
}
