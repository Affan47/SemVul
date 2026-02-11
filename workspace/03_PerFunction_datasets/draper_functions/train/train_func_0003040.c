unixAccess(
  unqlite_vfs *NotUsed,
  const char *zPath,
  int flags,
  int *pResOut
){
  int amode = 0;
  SXUNUSED(NotUsed);
  switch( flags ){
    case UNQLITE_ACCESS_EXISTS:
      amode = F_OK;
      break;
    case UNQLITE_ACCESS_READWRITE:
      amode = W_OK|R_OK;
      break;
    case UNQLITE_ACCESS_READ:
      amode = R_OK;
      break;
    default:

      break;
  }
  *pResOut = (access(zPath, amode)==0);
  if( flags==UNQLITE_ACCESS_EXISTS && *pResOut ){
    struct stat buf;
    if( 0==stat(zPath, &buf) && buf.st_size==0 ){
      *pResOut = 0;
    }
  }
  return UNQLITE_OK;
}
