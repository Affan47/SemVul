getvalue (SANE_Handle h, SANE_Int option, void *v)
{
  struct device_s *dev = (struct device_s *) h;

  if (option != COLOR_OFFSET)
    *((SANE_Word *) v) = dev->optionw[option];
  else
    {
      strcpy ((char *) v,
	      dev->optiond[option].constraint.string_list[dev->
							  optionw[option]]);
    }
  return SANE_STATUS_GOOD;
}
