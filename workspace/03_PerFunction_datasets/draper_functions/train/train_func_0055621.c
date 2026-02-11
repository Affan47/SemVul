json_user_list(){
  cson_value * payV = NULL;
  Stmt q;
  if(!g.perm.Admin && !g.perm.Setup){
    json_set_err(FSL_JSON_E_DENIED,
                 "Requires 'a' or 's' privileges.");
    return NULL;
  }
  db_prepare(&q,"SELECT uid AS uid,"
             " login AS name,"
             " cap AS capabilities,"
             " info AS info,"
             " mtime AS timestamp"
             " FROM user ORDER BY login");
  payV = json_stmt_to_array_of_obj(&q, NULL);
  db_finalize(&q);
  if(NULL == payV){
    json_set_err(FSL_JSON_E_UNKNOWN,
                 "Could not convert user list to JSON.");
  }
  return payV;
}
