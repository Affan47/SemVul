print_ink(stpi_dither_t *d, unsigned char *tptr, const stpi_ink_defn_t *ink,
	  unsigned char bit, int length)
{
  int j;

  if (tptr != 0)
    {
      tptr += d->ptr_offset;
      switch(ink->bits)
	{
	case 1:
	  tptr[0] |= bit;
	  return;
	case 2:
	  tptr[length] |= bit;
	  return;
	case 3:
	  tptr[0] |= bit;
	  tptr[length] |= bit;
	  return;
	default:
	  for (j=1; j <= ink->bits; j+=j, tptr += length)
	    {
	      if (j & ink->bits)
		*tptr |= bit;
	    }
	  return;
	}
    }
}
