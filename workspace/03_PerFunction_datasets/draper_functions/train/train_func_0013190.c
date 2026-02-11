open(void)
{
  ipcWarn(wrnlvl(),"%t AipcListener::open\n");
  MSProtocolListener::open();
  if (_zeroPort)
  {
    _hostPort.set(host(),getListenPort());
    ipcWarn(wrnlvl(),"%t   port fixed at %d\n",port());
  }
}
