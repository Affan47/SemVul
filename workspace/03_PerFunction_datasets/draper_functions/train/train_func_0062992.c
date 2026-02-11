m68hc11_function_arg_advance (cum, mode, type, named)
     CUMULATIVE_ARGS *cum;
     enum machine_mode mode;
     tree type;
     int named ATTRIBUTE_UNUSED;
{
  if (mode != BLKmode)
    {
      if (cum->words == 0 && GET_MODE_SIZE (mode) == 4)
	{
	  cum->nregs = 2;
	  cum->words = GET_MODE_SIZE (mode);
	}
      else
	{
	  cum->words += GET_MODE_SIZE (mode);
	  if (cum->words <= HARD_REG_SIZE)
	    cum->nregs = 1;
	}
    }
  else
    {
      cum->words += int_size_in_bytes (type);
    }
  return;
}
