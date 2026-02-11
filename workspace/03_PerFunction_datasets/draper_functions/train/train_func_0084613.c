ipcSend(int handle_,A msg_)
{
  H_SRVPTR("%t ipcSend\n");
  switch(srvptr->serviceType()) {
  case 1:
    return ((AipcConnection *)srvptr)->send(msg_);
  default: return -1;
  }
}
