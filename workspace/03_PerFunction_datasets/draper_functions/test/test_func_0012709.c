gt_seq_info_cache_get(GtSeqInfoCache *sic, const char *key)
{
  gt_assert(sic);
  return gt_hashmap_get(sic->cache, key);
}
