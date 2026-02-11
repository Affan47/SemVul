avgFinalize(sqlite_func *context){
  SumCtx *p;
  p = sqlite_aggregate_context(context, sizeof(*p));
  if( p && p->cnt>0 ){
    sqlite_set_result_double(context, p->sum/(double)p->cnt);
  }
}
