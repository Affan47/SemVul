redisRetVal_free(RedisRetVal *rv)
{
  int i;

  if (rv->bulk      != NULL) bstr_free(rv->bulk);
  if (rv->errorMsg  != NULL) bstr_free(rv->errorMsg);
  if (rv->line      != NULL) bstr_free(rv->line);
  if (rv->multibulk != NULL)
  {
    for (i=0; i < rv->multibulkSize; i++)
      if (rv->multibulk[i] != NULL) bstr_free(rv->multibulk[i]);
    free(rv->multibulk);
  }
  free(rv);
}
