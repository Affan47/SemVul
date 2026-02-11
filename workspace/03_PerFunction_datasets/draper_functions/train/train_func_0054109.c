read_current_value(StgTRecHeader *trec STG_UNUSED, StgTVar *tvar) {
  StgClosure *result;
  result = tvar -> current_value;

#if defined(STM_FG_LOCKS)
  while (GET_INFO(UNTAG_CLOSURE(result)) == &stg_TREC_HEADER_info) {
    TRACE("%p : read_current_value(%p) saw %p", trec, tvar, result);
    result = tvar -> current_value;
  }
#endif

  TRACE("%p : read_current_value(%p)=%p", trec, tvar, result);
  return result;
}
