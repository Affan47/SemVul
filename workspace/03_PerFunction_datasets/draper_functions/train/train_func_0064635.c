configure(Vector<String> &conf, ErrorHandler *errh)
{
  unsigned etht;
  if (cp_va_kparse(conf, this, errh,
		   "ETHERTYPE", cpkP+cpkM, cpUnsigned, &etht,
		   "SRC", cpkP+cpkM, cpEthernetAddress, &_ethh.ether_shost,
		   "DST", cpkP+cpkM, cpEthernetAddress, &_ethh.ether_dhost,
		   cpEnd) < 0)
    return -1;
  if (etht > 0xFFFF)
    return errh->error("argument 1 (Ethernet encapsulation type) must be <= 0xFFFF");
  _ethh.ether_type = htons(etht);
  return 0;
}
