procout(const char *dbname, int id, const char *expr){
  ESTDB *db;
  int ecode;
  if(!(db = est_db_open(dbname, ESTDBWRITER, &ecode))){
    printferror("%s: %s", dbname, est_err_msg(ecode));
    return 1;
  }
  est_db_set_informer(db, dbinform, NULL);
  if(expr && (id = est_db_uri_to_id(db, expr)) < 1 &&
     (id = est_db_uri_to_id(db, exprtouri(expr))) < 1){
    printferror("%s: %s", dbname, est_err_msg(est_db_error(db)));
    est_db_close(db, &ecode);
    return 1;
  }
  if(!est_db_out_doc(db, id, g_outopts)){
    printferror("%s: %s", dbname, est_err_msg(est_db_error(db)));
    est_db_close(db, &ecode);
    return 1;
  }
  printfinfo("%d: deleted", id);
  if(!est_db_close(db, &ecode)){
    printferror("%s: %s", dbname, est_err_msg(ecode));
    return 1;
  }
  return 0;
}
