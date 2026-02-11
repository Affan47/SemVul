gt_optionargsetsingle(const Optionargmodedesc *modedesc,
                          size_t numberofentries,
                          const char *optname,
                          const char *optionargument,
                          GtError *err)
{
  size_t modecount;

  gt_error_check(err);
  for (modecount=0; modecount < numberofentries; modecount++)
  {
    if (strcmp(optionargument,modedesc[modecount].name) == 0)
    {
      return (int) modedesc[modecount].bitmask;
    }
  }
  gt_error_set(err,"illegal argument \"%s\" to option %s",
                optionargument,optname);
  return -1;
}
