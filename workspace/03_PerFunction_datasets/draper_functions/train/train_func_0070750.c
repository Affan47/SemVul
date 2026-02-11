state_from_flags (enum pure_const_state_e *state, bool *looping,
	          int flags, bool cannot_lead_to_return)
{
  *looping = false;
  if (flags & ECF_LOOPING_CONST_OR_PURE)
    {
      *looping = true;
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, " looping");
    }
  if (flags & ECF_CONST)
    {
      *state = IPA_CONST;
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, " const\n");
    }
  else if (flags & ECF_PURE)
    {
      *state = IPA_PURE;
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, " pure\n");
    }
  else if (cannot_lead_to_return)
    {
      *state = IPA_PURE;
      *looping = true;
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, " ignoring side effects->pure looping\n");
    }
  else
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, " neihter\n");
      *state = IPA_NEITHER;
      *looping = true;
    }
}
