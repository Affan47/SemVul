trace_cache_get (void)
{
  unw_trace_cache_t *cache;
  if (likely (pthread_once != 0))
  {
    pthread_once(&trace_cache_once, &trace_cache_init_once);
    if (! (cache = tls_cache))
    {
      cache = trace_cache_create();
      pthread_setspecific(trace_cache_key, cache);
      tls_cache = cache;
    }
    Debug(5, "using cache %p\n", cache);
    return cache;
  }
  else
  {
    intrmask_t saved_mask;
    static unw_trace_cache_t *global_cache = 0;
    lock_acquire (&trace_init_lock, saved_mask);
    if (! global_cache)
    {
      mempool_init (&trace_cache_pool, sizeof (unw_trace_cache_t), 0);
      global_cache = trace_cache_create ();
    }
    cache = global_cache;
    lock_release (&trace_init_lock, saved_mask);
    Debug(5, "using cache %p\n", cache);
    return cache;
  }
}
