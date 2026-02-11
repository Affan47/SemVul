configure(Vector<String> &conf, ErrorHandler* errh)
{
  bool timestamp = false;
#ifdef CLICK_LINUXMODULE
  bool print_cpu = false;
#endif
  bool print_anno = false, bcontents;
  String label, contents = "HEX";
  unsigned bytes = 24;

  if (cp_va_kparse(conf, this, errh,
		   "LABEL", cpkP, cpString, &label,
		   "LENGTH", cpkP, cpInteger, &bytes,
		   "NBYTES", 0, cpInteger, &bytes,
		   "CONTENTS", 0, cpWord, &contents,
		   "TIMESTAMP", 0, cpBool, &timestamp,
		   "PRINTANNO", 0, cpBool, &print_anno,
#ifdef CLICK_LINUXMODULE
		   "CPU", 0, cpBool, &print_cpu,
#endif
		   cpEnd) < 0)
    return -1;

  if (cp_bool(contents, &bcontents))
      _contents = bcontents;
  else if ((contents = contents.upper()), contents == "NONE")
      _contents = 0;
  else if (contents == "HEX")
      _contents = 1;
  else if (contents == "ASCII")
      _contents = 2;
  else
      return errh->error("bad contents value '%s'; should be 'NONE', 'HEX', or 'ASCII'", contents.c_str());

  _label = label;
  _bytes = bytes;
  _timestamp = timestamp;
  _print_anno = print_anno;
#ifdef CLICK_LINUXMODULE
  _cpu = print_cpu;
#endif
  return 0;
}
