chpho_get_str(int idx, int len, char *ch)
{
  int ofs=0, i;
  for(i=0; i < len; i++) {
	int u8len = u8cpy(&ch[ofs], tss.chpho[idx+i].ch);
    ofs+=u8len;
  }

  ch[ofs]=0;
}
