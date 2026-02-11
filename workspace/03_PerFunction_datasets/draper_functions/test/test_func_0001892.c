clear_gtab_buf_all()
{
  int i;
  for(i=0;i<ggg.gbufN;i++)
    free_gbuf(i);
  ggg.gbuf_cursor = ggg.gbufN=0;
  ggg.gtab_buf_select = 0;
  disp_gbuf();
}
