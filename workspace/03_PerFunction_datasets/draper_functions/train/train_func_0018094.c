output_gbuf()
{
  hide_gtab_pre_sel();

  if (!ggg.gbufN)
    return FALSE;
#if WIN32
  if (test_mode)
    return TRUE;
#endif
  char *bf=gen_buf_str(0, TRUE);
#if 0
  printf("out %s\n", bf);
#endif

#if 0

  char *p;
  for(p=bf; *p; p+=utf8_sz(p))
    inc_gtab_use_count(p);
#endif

  send_text(bf);
  free(bf);

  int i;
  for(i=0; i < ggg.gbufN;) {
    char t[MAX_CIN_PHR+1];
    t[0]=0;
    inc_gtab_use_count(gbuf[i].ch);

    int j;
    for(j=i; j < i+gbuf[i].plen; j++)
      strcat(t, gbuf[j].ch);

    if (!gbuf[i].plen)
      i++;
#if USE_TSIN
    else {
      u_int64_t kk[MAX_PHRASE_LEN];
	  extract_gtab_key(i, gbuf[i].plen, kk);
	  inc_dec_tsin_use_count(kk, t, gbuf[i].plen);
      i+=gbuf[i].plen;
    }
#endif
  }


  clear_gtab_buf_all();
  ClrIn();
  return TRUE;
}
