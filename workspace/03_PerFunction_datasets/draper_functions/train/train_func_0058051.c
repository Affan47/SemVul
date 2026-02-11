detect_caches_cpuid4 (struct cache_desc *level1, struct cache_desc *level2,
		      struct cache_desc *level3)
{
  struct cache_desc *cache;

  unsigned eax, ebx, ecx, edx;
  int count;

  for (count = 0;; count++)
    {
      __cpuid_count(4, count, eax, ebx, ecx, edx);
      switch (eax & 0x1f)
	{
	case CACHE_END:
	  return;
	case CACHE_DATA:
	case CACHE_UNIFIED:
	  {
	    switch ((eax >> 5) & 0x07)
	      {
	      case 1:
		cache = level1;
		break;
	      case 2:
		cache = level2;
		break;
	      case 3:
		cache = level3;
		break;
	      default:
		cache = NULL;
	      }

	    if (cache)
	      {
		unsigned sets = ecx + 1;
		unsigned part = ((ebx >> 12) & 0x03ff) + 1;

		cache->assoc = ((ebx >> 22) & 0x03ff) + 1;
		cache->line = (ebx & 0x0fff) + 1;

		cache->sizekb = (cache->assoc * part
				 * cache->line * sets) / 1024;
	      }
	  }
	default:
	  break;
	}
    }
}
