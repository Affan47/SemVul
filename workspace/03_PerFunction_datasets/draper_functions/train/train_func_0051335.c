joinStep(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  StrBuffer *p;
  UNUSED_PARAMETER(argc);
  p = (StrBuffer *)sqlite3_aggregate_context(context, sizeof(StrBuffer));
  if( p->zBuf==0 ){
    p->zBuf = sqlite3_mprintf("%s", sqlite3_value_text(argv[0]));
  }else{
    char *zTmp = p->zBuf;
    p->zBuf = sqlite3_mprintf("%s%s%s",
        zTmp, sqlite3_value_text(argv[1]), sqlite3_value_text(argv[0])
    );
    sqlite3_free(zTmp);
  }
}
