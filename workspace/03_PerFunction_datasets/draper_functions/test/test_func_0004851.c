configure(Vector<String> &conf, ErrorHandler *errh)
{
  unsigned bit_error;
  String kind_str = "flip";
  bool on = true;
  if (cp_va_kparse(conf, this, errh,
		   "P", cpkP+cpkM, cpUnsignedReal2, 28, &bit_error,
		   "KIND", cpkP, cpString, &kind_str,
		   "ACTIVE", cpkP, cpBool, &on,
		   cpEnd) < 0)
    return -1;

  unsigned kind;
  if (kind_str == "flip" || kind_str == "")
    kind = 2;
  else if (kind_str == "set")
    kind = 1;
  else if (kind_str == "clear")
    kind = 0;
  else
    return errh->error("bad action '%s' (must be 'set', 'clear', or 'flip')",
		       kind_str.c_str());

  if (bit_error > 0x10000000)
    return errh->error("drop probability must be between 0 and 1");
  if (bit_error == 0)
    errh->warning("zero bit error probability (underflow?)");


  set_bit_error(bit_error);
  _kind = kind;
  _on = on;

  return 0;
}
