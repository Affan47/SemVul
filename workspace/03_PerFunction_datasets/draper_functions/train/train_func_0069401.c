lock_tvar(StgTRecHeader *trec STG_UNUSED,
                             StgTVar *s STG_UNUSED) {
  StgClosure *result;
  TRACE("%p : lock_tvar(%p)", trec, s);
  result = s -> current_value;
  return result;
}
