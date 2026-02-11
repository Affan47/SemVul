db_timespan_name(double rSpan){
  if( rSpan<0 ) rSpan = -rSpan;
  rSpan *= 24.0*3600.0;
  if( rSpan<120.0 ){
    return sqlite3_mprintf("%.1f seconds", rSpan);
  }
  rSpan /= 60.0;
  if( rSpan<90.0 ){
    return sqlite3_mprintf("%.1f minutes", rSpan);
  }
  rSpan /= 60.0;
  if( rSpan<=48.0 ){
    return sqlite3_mprintf("%.1f hours", rSpan);
  }
  rSpan /= 24.0;
  if( rSpan<=365.0 ){
    return sqlite3_mprintf("%.1f days", rSpan);
  }
  rSpan /= 356.24;
  return sqlite3_mprintf("%.1f years", rSpan);
}
