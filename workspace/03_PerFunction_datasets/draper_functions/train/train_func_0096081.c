send_gamma_table (Mustek_Scanner * s)
{
  SANE_Status status;

  if (s->one_pass_color_scan)
    {
      if (s->hw->flags & MUSTEK_FLAG_N)


	status = gamma_correction (s, MUSTEK_CODE_GRAY);
      else
	{
	  status = gamma_correction (s, MUSTEK_CODE_RED);
	  if (status != SANE_STATUS_GOOD)
	    return status;

	  status = gamma_correction (s, MUSTEK_CODE_GREEN);
	  if (status != SANE_STATUS_GOOD)
	    return status;

	  status = gamma_correction (s, MUSTEK_CODE_BLUE);
	}
    }
  else
    status = gamma_correction (s, MUSTEK_CODE_GRAY);
  return status;
}
