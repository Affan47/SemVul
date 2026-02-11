report_query_authorizer(
  void *pError,
  int code,
  const char *zArg1,
  const char *zArg2,
  const char *zArg3,
  const char *zArg4
){
  int rc = SQLITE_OK;
  if( *(char**)pError ){

    return SQLITE_OK;
  }
  switch( code ){
    case SQLITE_SELECT:
    case SQLITE_FUNCTION: {
      break;
    }
    case SQLITE_READ: {
      static const char *const azAllowed[] = {
         "ticket",
         "ticketchng",
         "blob",
         "filename",
         "mlink",
         "plink",
         "event",
         "tag",
         "tagxref",
      };
      int i;
      for(i=0; i<sizeof(azAllowed)/sizeof(azAllowed[0]); i++){
        if( fossil_stricmp(zArg1, azAllowed[i])==0 ) break;
      }
      if( i>=sizeof(azAllowed)/sizeof(azAllowed[0]) ){
        *(char**)pError = mprintf("access to table \"%s\" is restricted",zArg1);
        rc = SQLITE_DENY;
      }else if( !g.perm.RdAddr && strncmp(zArg2, "private_", 8)==0 ){
        rc = SQLITE_IGNORE;
      }
      break;
    }
    default: {
      *(char**)pError = mprintf("only SELECT statements are allowed");
      rc = SQLITE_DENY;
      break;
    }
  }
  return rc;
}
