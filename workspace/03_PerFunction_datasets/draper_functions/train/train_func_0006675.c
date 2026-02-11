configure_inop_rhs(int iMask){
  Blob x;
  int i;
  const char *zSep = "";

  blob_zero(&x);
  blob_append(&x, "(", 1);
  for(i=0; i<count(aConfig); i++){
    if( (aConfig[i].groupMask & iMask)==0 ) continue;
    if( aConfig[i].zName[0]=='@' ) continue;
    blob_appendf(&x, "%s'%s'", zSep, aConfig[i].zName);
    zSep = ",";
  }
  blob_append(&x, ")", 1);
  return blob_str(&x);
}
