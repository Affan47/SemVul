GC_finalize_all()
{
    DCL_LOCK_STATE;

    DISABLE_SIGNALS();
    LOCK();
    while (GC_fo_entries > 0) {
      GC_enqueue_all_finalizers();
      UNLOCK();
      ENABLE_SIGNALS();
      GC_INVOKE_FINALIZERS();
      DISABLE_SIGNALS();
      LOCK();
    }
    UNLOCK();
    ENABLE_SIGNALS();
}
