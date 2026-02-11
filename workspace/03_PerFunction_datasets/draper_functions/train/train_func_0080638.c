ipcConnectN(A afunc, A aname)
{
  C *serviceName=getString(aname);
  int protocolidx;
  AipcService *nSrv;

  InitializeIfNeeded();
  ipcWarn(0,"%t ipcConnectN:\n");

  if (!serviceName||!QF(afunc))return -1;

  AipcHostPortProtocol *ahpp=new AipcHostPortProtocol(serviceName);


  S protocolSym=si((char *)ahpp->protocol());

  ipcWarn(0,"%t ipcConnectN: name:%s host:%s port:%d protocol:%s\n",
	serviceName,ahpp->host(),ahpp->port(),ahpp->protocol());

  protocolidx=lookupProtocol(protocolSym);
  switch(protocolidx) {
  case 0: nSrv=new pA_Connection(*ahpp,afunc); break;
  case 1: nSrv=new pRaw_Connection(*ahpp,afunc); break;
  case 4: nSrv=new pIpc_Connection(*ahpp,afunc); break;
  case 5: {
    Warn("%t ipcConnectHPP: unsupported protocol:%s\n",protocolSym->n);
    return -1;
  }
  case 6: nSrv=new pString_Connection(*ahpp,afunc); break;
  case 7: nSrv=new pSimple_Connection(*ahpp,afunc); break;
  default:
    Warn("%t ipcConnectN: unknown protocol:%s\n",protocolSym->n);
    return -1;
  }
  return nSrv->handle();
}
