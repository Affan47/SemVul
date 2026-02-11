check_db3() {
  GWEN_DB_NODE *cfg;
  GWEN_DB_NODE *db1;
  GWEN_DB_NODE *db2;

  cfg=GWEN_DB_Group_new("config");
  if (cfg==NULL) {
    fprintf(stderr, "ERROR in db3: Could not create group.\n");
    return 2;
  }

  db1=GWEN_DB_GetGroup(cfg, 0, "test1");
  if (db1==NULL) {
    fprintf(stderr, "ERROR in db3: Could not create group [test1].\n");
    return 2;
  }

  db2=GWEN_DB_GetGroup(cfg, 0, "test1/test11");
  if (db2==NULL) {
    fprintf(stderr, "ERROR in db3: Could not create group [test1/test11].\n");
    return 2;
  }

  GWEN_DB_Group_free(cfg);
  return 0;
}
