calc_parameters (Lexmark_Device * lexmark_device)
{
  if (strcmp (lexmark_device->val[OPT_MODE].s,
	      SANE_VALUE_SCAN_MODE_LINEART) == 0)
    {
      lexmark_device->opt[OPT_THRESHOLD].cap &= ~SANE_CAP_INACTIVE;
    }
  else
    {
      lexmark_device->opt[OPT_THRESHOLD].cap |= SANE_CAP_INACTIVE;
    }


  if (lexmark_device->val[OPT_MANUAL_GAIN].w == SANE_TRUE)
    {
      if (strcmp (lexmark_device->val[OPT_MODE].s, SANE_VALUE_SCAN_MODE_COLOR)
	  != 0)
	{
	  lexmark_device->opt[OPT_GRAY_GAIN].cap &= ~SANE_CAP_INACTIVE;
	  lexmark_device->opt[OPT_RED_GAIN].cap |= SANE_CAP_INACTIVE;
	  lexmark_device->opt[OPT_GREEN_GAIN].cap |= SANE_CAP_INACTIVE;
	  lexmark_device->opt[OPT_BLUE_GAIN].cap |= SANE_CAP_INACTIVE;
	}
      else
	{
	  lexmark_device->opt[OPT_GRAY_GAIN].cap |= SANE_CAP_INACTIVE;
	  lexmark_device->opt[OPT_RED_GAIN].cap &= ~SANE_CAP_INACTIVE;
	  lexmark_device->opt[OPT_GREEN_GAIN].cap &= ~SANE_CAP_INACTIVE;
	  lexmark_device->opt[OPT_BLUE_GAIN].cap &= ~SANE_CAP_INACTIVE;
	}
    }
  else
    {
      lexmark_device->opt[OPT_GRAY_GAIN].cap |= SANE_CAP_INACTIVE;
      lexmark_device->opt[OPT_RED_GAIN].cap |= SANE_CAP_INACTIVE;
      lexmark_device->opt[OPT_GREEN_GAIN].cap |= SANE_CAP_INACTIVE;
      lexmark_device->opt[OPT_BLUE_GAIN].cap |= SANE_CAP_INACTIVE;
    }
}
