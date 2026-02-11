disp_current_sel_page()
{
  int i;

  clear_sele();

  for(i=0; i < phkbm.selkeyN; i++) {
    int idx = tss.current_page + i;

    if (idx < phrase_count) {
      int tlen = utf8_tlen((char *)selstr[i], sellen[i]);
      set_sele_text(phrase_count + pho_count, i, (char *)selstr[i], tlen);
    } else
    if (idx < phrase_count + pho_count) {
      int v = idx - phrase_count + tss.startf;
      char *tstr = pho_idx_str(v);
      set_sele_text(phrase_count + pho_count, i, tstr, -1);
    } else
      break;
  }

  if (tss.current_page + phkbm.selkeyN < phrase_count + pho_count) {
    disp_arrow_down();
  }

  if (tss.current_page > 0)
    disp_arrow_up();

  disp_tsin_select(tss.c_idx==tss.c_len?tss.c_idx-1:tss.c_idx);
}
