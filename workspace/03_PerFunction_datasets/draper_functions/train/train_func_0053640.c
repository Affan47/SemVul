prbuf()
{
  int i;


  for(i=0;i<tss.c_len;i++)
	if (!(tss.chpho[i].flag & FLAG_CHPHO_PHO_PHRASE))
		tss.chpho[i].ch=tss.chpho[i].cha;

  for(i=0; i < tss.c_len; i++)
    disp_char_chbuf(i);

  for(i=tss.c_len; i < MAX_PH_BF_EXT; i++) {
    hide_char(i);
  }

  drawcursor();
}
