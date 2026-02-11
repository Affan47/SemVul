configure(Vector<String> &conf, ErrorHandler *errh)
{
  unsigned dscp_val;
  if (cp_va_kparse(conf, this, errh,
		   "DSCP", cpkP+cpkM, cpUnsigned, &dscp_val,
		   cpEnd) < 0)
    return -1;
  if (dscp_val > 0x3F)
    return errh->error("diffserv code point out of range");


  _dscp = (dscp_val << 2);
  return 0;
}
