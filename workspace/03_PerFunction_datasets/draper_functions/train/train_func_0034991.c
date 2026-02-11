agent_flush_cache (void)
{
  ITEM r;

  if (DBG_CACHE)
    log_debug ("agent_flush_cache\n");

  for (r=thecache; r; r = r->next)
    {
      if (!r->lockcount && r->pw)
        {
          if (DBG_CACHE)
            log_debug ("  flushing `%s'\n", r->key);
          release_data (r->pw);
          r->pw = NULL;
          r->accessed = 0;
        }
      else if (r->lockcount && r->pw)
        {
          if (DBG_CACHE)
            log_debug ("    marked `%s' for flushing\n", r->key);
          r->accessed = 0;
          r->ttl = 0;
        }
    }
}
