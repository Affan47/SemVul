login_group_join(
  const char *zRepo,
  const char *zLogin,
  const char *zPassword,
  const char *zNewName,
  char **pzErrMsg
){
  Blob fullName;
  sqlite3 *pOther;
  int rc;
  char *zOtherProjCode;
  char *zPwHash;
  char *zSelfRepo;
  char *zSelfLabel;
  char *zSelfProjCode;
  char *zSql;
  const char *zSelf;

  *pzErrMsg = 0;
  zSelf = db_name("repository");


  file_canonical_name(zRepo, &fullName, 0);
  zRepo = mprintf(blob_str(&fullName));
  blob_reset(&fullName);


  file_canonical_name(g.zRepositoryName, &fullName, 0);
  zSelfRepo = mprintf(blob_str(&fullName));
  blob_reset(&fullName);
  zSelfProjCode = db_get("project-code", "unknown");
  zSelfLabel = db_get("project-name", 0);
  if( zSelfLabel==0 ){
    zSelfLabel = zSelfProjCode;
  }


  if( fossil_strcmp(zRepo, zSelfRepo)==0 ){
    *pzErrMsg = mprintf("The \"other\" repository is the same as this one.");
    return;
  }


  if( file_size(zRepo)<0 ){
    *pzErrMsg = mprintf("repository file \"%s\" does not exist", zRepo);
    return;
  }
  rc = sqlite3_open(zRepo, &pOther);
  if( rc!=SQLITE_OK ){
    *pzErrMsg = mprintf(sqlite3_errmsg(pOther));
  }else{
    rc = sqlite3_exec(pOther, "SELECT count(*) FROM user", 0, 0, pzErrMsg);
  }
  sqlite3_close(pOther);
  if( rc ) return;


  db_attach(zRepo, "other");
  zOtherProjCode = db_text("x", "SELECT value FROM other.config"
                                " WHERE name='project-code'");
  zPwHash = sha1_shared_secret(zPassword, zLogin, zOtherProjCode);
  if( !db_exists(
    "SELECT 1 FROM other.user"
    " WHERE login=%Q AND cap GLOB '*s*'"
    "   AND (pw=%Q OR pw=%Q)",
    zLogin, zPassword, zPwHash)
  ){
    db_detach("other");
    *pzErrMsg = "The supplied username/password does not correspond to a"
                " user Setup permission on the other repository.";
    return;
  }


  zSelfProjCode = abbreviated_project_code(zSelfProjCode);
  zOtherProjCode = abbreviated_project_code(zOtherProjCode);
  db_begin_transaction();
  db_multi_exec(
    "DELETE FROM %s.config WHERE name GLOB 'peer-*';"
    "INSERT INTO %s.config(name,value) VALUES('peer-repo-%s',%Q);"
    "INSERT INTO %s.config(name,value) "
    "  SELECT 'peer-name-%q', value FROM other.config"
    "   WHERE name='project-name';",
    zSelf,
    zSelf, zOtherProjCode, zRepo,
    zSelf, zOtherProjCode
  );
  db_multi_exec(
    "INSERT OR IGNORE INTO other.config(name,value)"
    " VALUES('login-group-name',%Q);"
    "INSERT OR IGNORE INTO other.config(name,value)"
    " VALUES('login-group-code',lower(hex(randomblob(8))));",
    zNewName
  );
  db_multi_exec(
    "REPLACE INTO %s.config(name,value)"
    "  SELECT name, value FROM other.config"
    "   WHERE name GLOB 'peer-*' OR name GLOB 'login-group-*'",
    zSelf
  );
  db_end_transaction(0);
  db_multi_exec("DETACH other");


  zSql = mprintf(
    "BEGIN;"
    "REPLACE INTO config(name,value,mtime) VALUES('peer-name-%q',%Q,now());"
    "REPLACE INTO config(name,value,mtime) VALUES('peer-repo-%q',%Q,now());"
    "COMMIT;",
    zSelfProjCode, zSelfLabel, zSelfProjCode, zSelfRepo
  );
  login_group_sql(zSql, "<li> ", "</li>", pzErrMsg);
  fossil_free(zSql);
}
