stmCondemnTransaction(Capability *cap,
                           StgTRecHeader *trec) {
  TRACE("%p : stmCondemnTransaction", trec);
  ASSERT (trec != NO_TREC);
  ASSERT ((trec -> state == TREC_ACTIVE) ||
          (trec -> state == TREC_WAITING) ||
          (trec -> state == TREC_CONDEMNED));

  lock_stm(trec);
  if (trec -> state == TREC_WAITING) {
    ASSERT (trec -> enclosing_trec == NO_TREC);
    TRACE("%p : stmCondemnTransaction condemning waiting transaction", trec);
    remove_watch_queue_entries_for_trec(cap, trec);
  }
  trec -> state = TREC_CONDEMNED;
  unlock_stm(trec);

  TRACE("%p : stmCondemnTransaction done", trec);
}
