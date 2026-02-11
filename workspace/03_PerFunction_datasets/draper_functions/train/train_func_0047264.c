free_dither_ordered(stpi_dither_t *d)
{
  int i;
  stpi_dither_channel_t *dc0 = &CHANNEL(d, 0);
  stpi_ordered_t *o0 = dc0->aux_data;
  stpi_new_ordered_t *no0 = NULL;
  if (o0)
    no0 = o0->ord_new;
  for (i = CHANNEL_COUNT(d) - 1; i >= 0 ; i--)
    {
      stpi_dither_channel_t *dc = &CHANNEL(d, i);
      if (dc->aux_data)
	{
	  stpi_ordered_t *ord = (stpi_ordered_t *) dc->aux_data;
	  if (ord->ord_new && (i == 0 || ord->ord_new != no0))
	    {
	      stpi_new_ordered_t *no = (stpi_new_ordered_t *) ord->ord_new;
	      if (no->drops)
		stp_free(no->drops);
	      if (no->lut)
		stp_free(no->lut);
	      stp_free(no);
	    }
	  stp_free(dc->aux_data);
	  dc->aux_data = NULL;
	}
    }
  stp_free(d->aux_data);
}
