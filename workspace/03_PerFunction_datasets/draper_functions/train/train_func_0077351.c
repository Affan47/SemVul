tsin_page_down()
{
  if (!tss.sel_pho)
    return tss.c_len;

  tss.pho_menu_idx = 0;
  tss.current_page = tss.current_page + phkbm.selkeyN;
  if (tss.current_page >= phrase_count + pho_count)
    tss.current_page = 0;

  disp_current_sel_page();

  return TRUE;
}
