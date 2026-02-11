copyfile(FILE *sf, copyfile_die_fn *sdie, const char *sxi,
		     FILE *df, copyfile_die_fn *ddie, const char *dxi,
		     uint64_t lstart, int amsender) {
  struct timespec ts_last;
  int now, r;
  uint64_t l=lstart, done=0;

  ts_last= ts_sendstart;

  while (l>0) {
    now= l < sizeof(mainbuf) ? l : sizeof(mainbuf);
    if (now > txblocksz) now= txblocksz;

    r= fread(mainbuf,1,now,sf);  if (r!=now) sdie(sf,sxi);
    r= fwrite(mainbuf,1,now,df);  if (r!=now) ddie(df,dxi);
    l -= now;
    done += now;

    if (verbose) {
      fprintf(stderr," %3d%% \r",
	      (int)(done*100.0/lstart));
      flushstderr();
    }
  }
}
