tcos_login(xmlrpc_env *const env, xmlrpc_value *const in, void *const serverContext)
#else
xmlrpc_value *tcos_login(xmlrpc_env *env, xmlrpc_value *in, void *ud)
#endif
 {
  char *login_ok;
  char *user;
  char *pass;


  xmlrpc_parse_value(env, in, "(ss)", &user, &pass);

  dbgtcos("tcosxmlrpc::tcos_login() user=\"%s\" pass=\"******\"\n");

  login_ok=validate_login(user, pass);


  if ( strcmp(login_ok,  LOGIN_OK ) == 0 )
    return xmlrpc_build_value(env, "s", LOGIN_OK_MSG);


  else if ( strcmp(login_ok,  LOGIN_NOUSER ) == 0 )
    return xmlrpc_build_value(env, "s", LOGIN_NOUSER_MSG);


  else if (  strcmp(login_ok,  LOGIN_NOPASS ) == 0 )
    return xmlrpc_build_value(env, "s", LOGIN_NOPASS_MSG);


  else if (  strcmp(login_ok,  LOGIN_NOPERMS ) == 0 )
    return xmlrpc_build_value(env, "s", LOGIN_NOPERMS_MSG);


  else if (  strcmp(login_ok,  LOGIN_EXPIRED ) == 0 )
    return xmlrpc_build_value(env, "s", LOGIN_EXPIRED_MSG);

  return xmlrpc_build_value(env, "s", LOGIN_ERROR);
}
