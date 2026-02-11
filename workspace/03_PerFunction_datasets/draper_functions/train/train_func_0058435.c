ipcDestroy(int handle_)
{
  H_SRVPTR("%t ipcDestroy\n");
  switch(srvptr->serviceType()) {
  case 1:
    delete (AipcConnection *)srvptr;
    break;
  case 2:
    delete (AipcListener *)srvptr;
    break;
  case 4:
    delete (TimrConnection *)srvptr;
    break;
  default: return -1;
  }
  return 0;
}
