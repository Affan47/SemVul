p7_hmmcache_Open(char *hmmfile, P7_HMMCACHE **ret_cache, char *errbuf)
{
  P7_HMMCACHE *cache    = NULL;
  P7_HMMFILE  *hfp      = NULL;
  P7_OPROFILE *om       = NULL;
  int          status;

  ESL_ALLOC(cache, sizeof(P7_HMMCACHE));
  cache->name      = NULL;
  cache->abc       = NULL;
  cache->list      = NULL;
  cache->lalloc    = 4096;
  cache->n         = 0;

  if ( ( status = esl_strdup(hmmfile, -1, &cache->name) != eslOK)) goto ERROR;
  ESL_ALLOC(cache->list, sizeof(P7_OPROFILE *) * cache->lalloc);

  if ( (status = p7_hmmfile_OpenE(hmmfile, NULL, &hfp, errbuf)) != eslOK) goto ERROR;

  while ((status = p7_oprofile_ReadMSV(hfp, &(cache->abc), &om)) == eslOK)
    {
      if (( status = p7_oprofile_ReadRest(hfp, om)) != eslOK) break;

      if (cache->n >= cache->lalloc) {
	ESL_REALLOC(cache->list, sizeof(char *) * cache->lalloc * 2);
	cache->lalloc *= 2;
      }

      cache->list[cache->n++] = om;
      om = NULL;
    }
  if (status != eslEOF)  { strncpy(errbuf, hfp->errbuf, eslERRBUFSIZE); goto ERROR; }


  p7_hmmfile_Close(hfp);
  *ret_cache = cache;
  return eslOK;

 ERROR:
  if (cache) p7_hmmcache_Close(cache);
  if (om)    p7_oprofile_Destroy(om);
  if (hfp)   p7_hmmfile_Close(hfp);
  return status;
}
