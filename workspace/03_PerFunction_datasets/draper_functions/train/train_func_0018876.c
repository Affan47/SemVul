in_this_repo(const char *zUuid){
  static Stmt q;
  int rc;
  int n;
  char zU2[UUID_SIZE+1];
  db_static_prepare(&q,
     "SELECT 1 FROM blob WHERE uuid>=:u AND uuid<:u2"
  );
  db_bind_text(&q, ":u", zUuid);
  n = (int)strlen(zUuid);
  if( n>=sizeof(zU2) ) n = sizeof(zU2)-1;
  memcpy(zU2, zUuid, n);
  zU2[n-1]++;
  zU2[n] = 0;
  db_bind_text(&q, ":u2", zU2);
  rc = db_step(&q);
  db_reset(&q);
  return rc==SQLITE_ROW;
}
