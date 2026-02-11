gbuf_next_pg()
{
  ggg.pg_idx += page_len();
  if (ggg.pg_idx >= ggg.total_matchN)
    ggg.pg_idx = 0;

  gtab_disp_sel();
}
