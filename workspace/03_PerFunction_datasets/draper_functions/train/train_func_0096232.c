print_color_ordered_new(const stpi_dither_t *d, stpi_dither_channel_t *dc,
			int val, int x, int y, unsigned char bit, int length)
{
  int i;
  int j;
  unsigned bits;
  int levels = dc->nlevels - 1;
  unsigned dpoint = ditherpoint(d, &(dc->dithermat), x);
  const stpi_ordered_t *o = (const stpi_ordered_t *) dc->aux_data;
  const stpi_new_ordered_t *ord = (const stpi_new_ordered_t *) o->ord_new;
  unsigned short swhere = (unsigned short) val;
  unsigned short *where = ord ? ord->lut + (val * levels) : &swhere;


  for (i = levels - 1; i >= 0; i--)
    {
      if (dpoint < where[i])
	{
	  stpi_dither_segment_t *dd = &(dc->ranges[i]);
	  bits = dd->upper->bits;
	  if (bits)
	    {
	      unsigned char *tptr = dc->ptr + d->ptr_offset;


	      set_row_ends(dc, x);
	      for (j = 1; j <= bits; j += j, tptr += length)
		{
		  if (j & bits)
		    tptr[0] |= bit;
		}

	    }
	  return;
	}
    }
}
