login_as_user(const char *zUser){
  char *zCap = "";


  memset( &g.perm, 0, sizeof(g.perm) );


  g.userUid = db_int(0, "SELECT uid FROM user WHERE login=%Q", zUser);
  if( g.userUid==0 ){
    zUser = 0;
    g.userUid = db_int(0, "SELECT uid FROM user WHERE login='nobody'");
  }
  if( g.userUid ){
    zCap = db_text("", "SELECT cap FROM user WHERE uid=%d", g.userUid);
  }
  if( fossil_strcmp(zUser,"nobody")==0 ) zUser = 0;
  g.zLogin = fossil_strdup(zUser);


  login_set_capabilities(zCap, 0);
  login_anon_once = 1;
  login_set_anon_nobody_capabilities();
}
