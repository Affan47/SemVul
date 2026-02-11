configure(Vector<String> &conf, ErrorHandler *errh)
{
  unsigned etht = 0x0800;
  memset(&_ethh.ether_shost, 1, 6);
  memset(&_ethh.ether_dhost, 2, 6);
  if (cp_va_kparse(conf, this, errh,
		   "ETHERTYPE", cpkP, cpUnsigned, &etht,
		   "SRC", cpkP, cpEthernetAddress, &_ethh.ether_shost,
		   "DST", cpkP, cpEthernetAddress, &_ethh.ether_dhost,
		   cpEnd) < 0)
    return -1;
  if (etht > 0xFFFF)
    return errh->error("argument 1 (Ethernet encapsulation type) must be <= 0xFFFF");
  _ethh.ether_type = htons(etht);
  return 0;
}
