configure(Vector<String> &conf, ErrorHandler *errh)
{
  if (cp_va_kparse(conf, this, errh,
		   "OFFSET", cpkP+cpkM, cpUnsigned, &_offset,
		   "LENGTH", cpkP+cpkM, cpUnsigned, &_length,
		   cpEnd) < 0)
    return -1;
  if (_length == 0)
    return errh->error("length must be > 0");
  return 0;
}
