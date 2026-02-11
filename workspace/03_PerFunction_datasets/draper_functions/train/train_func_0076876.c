set_automatic_value (P5_Session * s, int option, SANE_Int * myinfo)
{
  SANE_Status status = SANE_STATUS_GOOD;
  SANE_Int i, min;
  SANE_Word *dpi_list;

  switch (option)
    {
    case OPT_TL_X:
      s->options[OPT_TL_X].value.w = x_range.min;
      *myinfo |= SANE_INFO_RELOAD_PARAMS;
      break;
    case OPT_TL_Y:
      s->options[OPT_TL_Y].value.w = y_range.min;
      *myinfo |= SANE_INFO_RELOAD_PARAMS;
      break;
    case OPT_BR_X:
      s->options[OPT_BR_X].value.w = x_range.max;
      *myinfo |= SANE_INFO_RELOAD_PARAMS;
      break;
    case OPT_BR_Y:
      s->options[OPT_BR_Y].value.w = y_range.max;
      *myinfo |= SANE_INFO_RELOAD_PARAMS;
      break;
    case OPT_RESOLUTION:

      dpi_list =
	(SANE_Word *) s->options[OPT_RESOLUTION].descriptor.constraint.
	word_list;
      min = 65536;
      for (i = 1; i < dpi_list[0]; i++)
	{
	  if (dpi_list[i] < min)
	    min = dpi_list[i];
	}
      s->options[OPT_RESOLUTION].value.w = min;
      *myinfo |= SANE_INFO_RELOAD_PARAMS;
      break;
    case OPT_PREVIEW:
      s->options[OPT_PREVIEW].value.w = SANE_FALSE;
      *myinfo |= SANE_INFO_RELOAD_PARAMS;
      break;
    case OPT_MODE:
      if (s->options[OPT_MODE].value.s)
	free (s->options[OPT_MODE].value.s);
      s->options[OPT_MODE].value.s = strdup (mode_list[0]);
      *myinfo |= SANE_INFO_RELOAD_OPTIONS;
      *myinfo |= SANE_INFO_RELOAD_PARAMS;
      break;
    default:
      DBG (DBG_warn, "set_automatic_value: can't set unknown option %d\n",
	   option);
    }

  return status;
}
