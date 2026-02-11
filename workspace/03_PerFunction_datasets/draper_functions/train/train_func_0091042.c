pcl3_flag_mismatch_reporter(FILE *err,
  const struct s_eprn_Device *eprn, bool no_match)
{
  const char *epref = eprn->CUPS_messages? CUPS_ERRPREF: "";

  if (eprn->desired_flags == 0) {
    eprintf2(
      "%s" ERRPREF "The %s does not support the requested media properties.\n",
      epref, eprn->cap->name);
  }
  else if (eprn->desired_flags == MS_BIG_FLAG) {
    eprintf2("%s" ERRPREF "The %s does not support banner printing",
      epref, eprn->cap->name);
    if (!no_match) eprintf(" for this size");
    eprintf(".\n");
  }
  else if (eprn->desired_flags == PCL_CARD_FLAG) {
    eprintf2("%s" ERRPREF
      "The %s does not support a `Card' variant for ",
      epref, eprn->cap->name);
    if (no_match) eprintf("any"); else eprintf("this");
    eprintf(" size.\n");
  }
  else {
    eprintf1(
      "%s" ERRPREF "Banner printing on postcards?? You must be joking!\n",
      epref);
  }

  return;
}
