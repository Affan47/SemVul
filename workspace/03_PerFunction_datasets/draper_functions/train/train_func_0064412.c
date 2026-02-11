url_enable_proxy(const char *zMsg){
  const char *zProxy;
  zProxy = zProxyOpt;
  if( zProxy==0 ){
    zProxy = db_get("proxy", 0);
    if( zProxy==0 || zProxy[0]==0 || is_truth(zProxy) ){
      zProxy = fossil_getenv("http_proxy");
    }
  }
  if( zProxy && zProxy[0] && !is_false(zProxy)
      && !g.urlIsSsh && !g.urlIsFile ){
    char *zOriginalUrl = g.urlCanonical;
    char *zOriginalHost = g.urlHostname;
    char *zOriginalUser = g.urlUser;
    char *zOriginalPasswd = g.urlPasswd;
    unsigned uOriginalFlags = g.urlFlags;
    g.urlUser = 0;
    g.urlPasswd = "";
    url_parse(zProxy, 0);
    if( zMsg ) fossil_print("%s%s\n", zMsg, g.urlCanonical);
    g.urlPath = zOriginalUrl;
    g.urlHostname = zOriginalHost;
    if( g.urlUser ){
      char *zCredentials1 = mprintf("%s:%s", g.urlUser, g.urlPasswd);
      char *zCredentials2 = encode64(zCredentials1, -1);
      g.urlProxyAuth = mprintf("Basic %z", zCredentials2);
      free(zCredentials1);
    }
    g.urlUser = zOriginalUser;
    g.urlPasswd = zOriginalPasswd;
    g.urlFlags = uOriginalFlags;
  }
}
