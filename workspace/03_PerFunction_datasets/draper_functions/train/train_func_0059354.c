configure(Vector<String> &conf, ErrorHandler *errh)
{
  bool verbose = false;
  bool details = false;

  if (cp_va_kparse(conf, this, errh,
		   "VERBOSE", 0, cpBool, &verbose,
		   "DETAILS", 0, cpBool, &details,
		   cpEnd) < 0)
    return -1;

  _verbose = verbose;
  if (details)
    _reason_drops = new atomic_uint32_t[NREASONS];

  return 0;
}
