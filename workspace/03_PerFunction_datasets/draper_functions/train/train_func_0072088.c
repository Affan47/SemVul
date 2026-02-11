tcos_devices(xmlrpc_env *const env, xmlrpc_value *const in, void *const serverContext)
#else
xmlrpc_value *tcos_devices(xmlrpc_env *env, xmlrpc_value *in, void *ud)
#endif
 {
  FILE *fp;
  char line[BSIZE];
  char *option;
  char *cmdline;
  char mycmd[BSIZE];
  char *cookie;
  char *hostname;
  int xauth_ok;
  char *fret;
  UNUSED(fret);

  dbgtcos("tcosxmlrpc::tcos_devices() Init \n");


  xmlrpc_parse_value(env, in, "(ssss)", &option, &cmdline, &cookie, &hostname);
  if (env->fault_occurred)
    return xmlrpc_build_value(env, "s", "params error");

  dbgtcos("tcosxmlrpc::tcos_devices() option=%s cmdline=%s \n", option, cmdline);

  if (strcmp(option, "--getxdrivers") == 0 ) {
    dbgtcos("tcosxmlrpc::tcos_devices() --getxdrivers no xauth\n");
  }
  else {

    xauth_ok=handle_xauth(cookie,hostname);
    if( xauth_ok != XAUTH_OK ) {
      dbgtcos("tcos_devices() error: xauth access denied :::::: err number: %d\n", xauth_ok);
      return xmlrpc_build_value(env, "s", "error: xauth access denied" );
      }
  }


   snprintf( (char*) mycmd, BSIZE, "%s %s %s", DEVICES_WRAPPER, option, cmdline);

   fp=(FILE*)popen( mycmd , "r");
   if (fp == NULL)
     return xmlrpc_build_value(env, "s", DEVICES_READING_ERROR );


   strncpy(line, DEVICES_ERROR, BSIZE);

   fret=fgets( line, sizeof line, fp);
   remove_line_break(line);
   pclose(fp);
   dbgtcos("tcosxmlrpc::tcos_devices(%s) = %s \n", mycmd, line);

   if (env->fault_occurred) {
     return xmlrpc_build_value(env, "s", DEVICES_READING_ERROR);
   }


   return xmlrpc_build_value(env, "s", line );

}
