proclist(const char *dbname, int lp){
  ESTDB *db;
  const char *path;
  char *vbuf;
  int ecode, id;
  if(!(db = est_db_open(dbname, ESTDBREADER | g_oextmodes, &ecode))){
    printferror("%s: %s", dbname, est_err_msg(ecode));
    return 1;
  }
  if(!est_db_iter_init(db, NULL)){
    printferror("%s: %s", dbname, est_err_msg(est_db_error(db)));
    est_db_close(db, &ecode);
    return 1;
  }
  while((id = est_db_iter_next(db)) > 0){
    if((vbuf = est_db_get_doc_attr(db, id, ESTDATTRURI)) != NULL){
      printf("%d\t%s", id, vbuf);
      if(lp && (path = urltopath(vbuf)) != NULL){
        printf("\t%s", path);
      }
      printf("\n");
      free(vbuf);
    }
  }
  if(!est_db_close(db, &ecode)){
    printferror("%s: %s", dbname, est_err_msg(ecode));
    return 1;
  }
  return 0;
}
