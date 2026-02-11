procget(const char *dbname, const CBLIST *pidxs,
                   int id, const char *expr, const char *attr){
  ESTDB *db;
  ESTDOC *doc;
  char *draft;
  int i, ecode;
  if(!(db = est_db_open(dbname, ESTDBREADER | g_oextmodes, &ecode))){
    printferror("%s: %s", dbname, est_err_msg(ecode));
    return 1;
  }
  for(i = 0; i < cblistnum(pidxs); i++){
    est_db_add_pseudo_index(db, cblistval(pidxs, i, NULL));
  }
  if(expr && (id = est_db_uri_to_id(db, expr)) < 1 &&
     (id = est_db_uri_to_id(db, exprtouri(expr))) < 1){
    printferror("%s: %s", dbname, est_err_msg(est_db_error(db)));
    est_db_close(db, &ecode);
    return 1;
  }
  if(attr){
    if(!(draft = est_db_get_doc_attr(db, id, attr))){
      printferror("%s: %s", dbname, est_err_msg(est_db_error(db)));
      est_db_close(db, &ecode);
      return 1;
    }
    printf("%s\n", draft);
    free(draft);
  } else {
    if(!(doc = est_db_get_doc(db, id, 0))){
      printferror("%s: %s", dbname, est_err_msg(est_db_error(db)));
      est_db_close(db, &ecode);
      return 1;
    }
    draft = est_doc_dump_draft(doc);
    printf("%s", draft);
    free(draft);
    est_doc_delete(doc);
  }
  if(!est_db_close(db, &ecode)){
    printferror("%s: %s", dbname, est_err_msg(ecode));
    return 1;
  }
  return 0;
}
