p7_seqcache_Close(P7_SEQCACHE *cache)
{
  int i;

  if (cache->name)        free(cache->name);
  if (cache->id)          free(cache->id);
  if (cache->db)
    {
      for (i = 0; i < cache->db_cnt; ++i) {
	if (cache->db[i].list != NULL) free(cache->db[i].list);
      }
      free(cache->db);
    }
  if (cache->abc)         esl_alphabet_Destroy(cache->abc);
  if (cache->list)        free(cache->list);
  if (cache->residue_mem) free(cache->residue_mem);
  if (cache->header_mem)  free(cache->header_mem);
  free(cache);
}
