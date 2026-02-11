cp_va_kparse_remove_keywords(Vector<String> &conf,
#ifndef CLICK_TOOL
			     Element *context,
#endif
			     ErrorHandler *errh, ...)
{
  va_list val;
  va_start(val, errh);
  CpVaHelper cpva(cp_values, CP_VALUES_SIZE, true);
  int retval = cpva.develop_kvalues(val, errh);
  if (retval >= 0)
    retval = cpva.assign_arguments(conf, "argument", errh);
  if (retval >= 0)
    retval = cpva.parse_arguments("argument"  CP_PASS_CONTEXT, errh);
  va_end(val);


  if (retval >= 0) {
    int delta = 0;
    for (int i = 0; i < conf.size(); i++)
      if ((*cp_parameter_used)[i])
	delta++;
      else if (delta)
	conf[i - delta] = conf[i];
    conf.resize(conf.size() - delta);
  }

  return retval;
}
