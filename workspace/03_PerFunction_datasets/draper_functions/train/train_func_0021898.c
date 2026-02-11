ClrIn()
{
  bzero(ggg.inch,sizeof(ggg.inch));
  clr_seltab();
  ggg.total_matchN=ggg.pg_idx=ggg.more_pg=ggg.wild_mode=ggg.wild_page=ggg.last_idx=ggg.defselN=ggg.exa_match=
  ggg.spc_pressed=ggg.ci=ggg.invalid_spc=0;

  ggg.sel1st_i=MAX_SELKEY-1;

  clear_gtab_in_area();
  ggg.last_idx = 0;

  if (hime_pop_up_win && !gtab_has_input() && !tss.pre_selN)
    hide_win_gtab();

  clear_gtab_input_error_color();
  clear_page_label();

}
