stp_dither_internal(stp_vars_t *v, int row, const unsigned short *input,
		    int duplicate_line, int zero_mask,
		    const unsigned char *mask)
{
  int i;
  stpi_dither_t *d = (stpi_dither_t *) stp_get_component_data(v, "Dither");
  stpi_dither_finalize(v);
  stp_dither_matrix_set_row(&(d->dither_matrix), row);
  for (i = 0; i < CHANNEL_COUNT(d); i++)
    {
      CHANNEL(d, i).ptr = CHANNEL(d, i).ptr;
      if (CHANNEL(d, i).ptr)
	  memset(CHANNEL(d, i).ptr, 0,
		 (d->dst_width + 7) / 8 * CHANNEL(d, i).signif_bits);
      CHANNEL(d, i).row_ends[0] = -1;
      CHANNEL(d, i).row_ends[1] = -1;

      stp_dither_matrix_set_row(&(CHANNEL(d, i).dithermat), row);
      stp_dither_matrix_set_row(&(CHANNEL(d, i).pick), row);
    }
  d->ptr_offset = 0;
  (d->ditherfunc)(v, row, input, duplicate_line, zero_mask, mask);
}
