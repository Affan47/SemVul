lrc_getbf(void *lrch)

{
  int		bfsize;
  time_t	now;
  int		rc;
  char		buf[MAXERRMSG];
  char		errbuf[MAXERRMSG];

  if (loglevel)
    logit(LOG_DEBUG, "lrc_getbf:");
  bloomfilter.startlfns = table[T_LRCLFN].count;
  bfsize = bloomfilter.startlfns * lrc_bloomfilter_ratio;
  if (bfsize < MINBFSIZE)
    bfsize = MINBFSIZE;
  if (bf_init(&bloomfilter, bfsize, lrc_bloomfilter_numhash,
	      1) != GLOBUS_RLS_SUCCESS) {
    logit(LOG_WARNING, "lrc_getbf: bf_init(%d): No memory", bfsize);
    return;
  }
  if (loglevel)
    now = time(0);
  globus_mutex_lock(&bloomfilter.mtx);
  if ((rc = db_lrc_alllfn(lrch, bloomfiltercb, NULL,
			  errbuf)) != GLOBUS_RLS_SUCCESS)
    logit(LOG_WARNING, "lrc_getbf: db_lrc_alllfn: %s",
	  globus_rls_errmsg(rc, errbuf, buf, MAXERRMSG));
  else if (loglevel)
    logit(LOG_DEBUG, "lrc_getbf: Computing bloom filter took %d seconds",
	  time(0) - now);
  globus_mutex_unlock(&bloomfilter.mtx);
}
