collect_argument(Blob *pExtra, const char *zArg, const char *zShort){
  if( find_option(zArg, zShort, 0)!=0 ){
    blob_appendf(pExtra, " --%s", zArg);
  }
}
