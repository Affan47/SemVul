tcos_unlockcontroller(xmlrpc_env *const env, xmlrpc_value *const in, void *const serverContext)
#else
xmlrpc_value *tcos_unlockcontroller(xmlrpc_env *env, xmlrpc_value *in, void *ud)
#endif
 {
  char *user;
  char *pass;
  char *action;
  char *login_ok;


  xmlrpc_parse_value(env, in, "(sss)", &action, &user, &pass);
  if (env->fault_occurred)
    return xmlrpc_build_value(env, "s", "params error");


  login_ok=validate_login(user,pass);
  if( strcmp(login_ok,  LOGIN_OK ) != 0 )
    return xmlrpc_build_value(env, "s", login_ok );

  kill_exe(action);
  return xmlrpc_build_value(env, "s", "OK" );
}
