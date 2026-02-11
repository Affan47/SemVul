rid_from_uuid(Blob *pUuid, int phantomize, int isPrivate){
  static Stmt q;
  int rid;

  db_static_prepare(&q, "SELECT rid FROM blob WHERE uuid=:uuid");
  db_bind_str(&q, ":uuid", pUuid);
  if( db_step(&q)==SQLITE_ROW ){
    rid = db_column_int(&q, 0);
  }else{
    rid = 0;
  }
  db_reset(&q);
  if( rid==0 && phantomize ){
    rid = content_new(blob_str(pUuid), isPrivate);
  }
  return rid;
}
