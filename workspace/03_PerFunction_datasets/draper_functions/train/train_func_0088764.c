configure(Vector<String> &conf, ErrorHandler *errh)
{
  if (cp_va_kparse(conf, this, errh,
		   "MYADDR", cpkP+cpkM, cpIPAddress, &_preferred_addr,
		   "OTHERADDRS", cpkP, cpIPAddressList, &_my_addrs,
		   cpEnd) < 0)
    return -1;
  _my_addrs.push_back(_preferred_addr);
  return 0;
}
