back_pluggable_sockets_strict(struct_back * sback, httrackp * opt) {
  int n = opt->maxsoc - back_nsoc(sback);


  if (n > 0 && opt->maxconn > 0 && HTS_STAT.last_connect > 0) {
    TStamp opTime =
      HTS_STAT.last_request ? HTS_STAT.last_request : HTS_STAT.last_connect;
    TStamp cTime = mtime_local();
    TStamp lap = (cTime - opTime);
    TStamp minLap = (TStamp) (1000.0 / opt->maxconn);

    if (lap < minLap) {
      n = 0;
    } else if (minLap != 0) {
      int nMax = (int) (lap / minLap);

      n = min(n, nMax);
    }
  }

  return n;
}
