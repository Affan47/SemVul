init_tab_pp(gboolean init)
{
  if (!tss.chpho)
    tss.chpho=tzmalloc(CHPHO, MAX_PH_BF_EXT);


  init_pre_sel();

  if (!ch_pho)
    load_tab_pho_file();

  load_tsin_db();

  if (init)
    clr_ch_buf();

  show_tsin_stat();
  if (init)
    clear_ch_buf_sel_area();

  if (!hime_pop_up_win)
    show_win0();
}
