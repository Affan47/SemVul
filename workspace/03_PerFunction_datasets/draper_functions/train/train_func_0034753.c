finalize_row(stp_vars_t *v, int row)
{
  stpi_softweave_t *sw = get_sw(v);
  int i,j;
  stp_dprintf(STP_DBG_ROWS, v, "Finalizing row %d...\n", row);
  for (i = 0; i < sw->oversample; i++)
    {
      stp_weave_t w;
      stp_linecount_t *lines;

      for(j=0; j<sw->ncolors; j++)
        {
	  lines = stpi_get_linecount(v, sw, row, i, sw->head_offset[j]);
	  lines->v[j]++;
        }

      weave_parameters_by_row(v, sw, row, i, &w);
      if (w.physpassend == row)
	{
	  stp_dprintf(STP_DBG_ROWS, v,
		      "Pass=%d, physpassend=%d, row=%d, lineno=%d, flush..\n",
		      w.pass, w.physpassend, row, sw->lineno);
	  stpi_flush_passes(v, 0);
	}
    }
}
