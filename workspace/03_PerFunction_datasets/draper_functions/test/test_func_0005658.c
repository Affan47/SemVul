test_container_smartlist_digests(void)
{
  smartlist_t *sl = smartlist_new();


  smartlist_add(sl, tor_memdup("AAAAAAAAAAAAAAAAAAAA", DIGEST_LEN));
  smartlist_add(sl, tor_memdup("\00090AAB2AAAAaasdAAAAA", DIGEST_LEN));
  smartlist_add(sl, tor_memdup("\00090AAB2AAAAaasdAAAAA", DIGEST_LEN));
  test_eq(0, smartlist_digest_isin(NULL, "AAAAAAAAAAAAAAAAAAAA"));
  test_assert(smartlist_digest_isin(sl, "AAAAAAAAAAAAAAAAAAAA"));
  test_assert(smartlist_digest_isin(sl, "\00090AAB2AAAAaasdAAAAA"));
  test_eq(0, smartlist_digest_isin(sl, "\00090AAB2AAABaasdAAAAA"));


  smartlist_sort_digests(sl);
  test_memeq(smartlist_get(sl, 0), "\00090AAB2AAAAaasdAAAAA", DIGEST_LEN);
  test_memeq(smartlist_get(sl, 1), "\00090AAB2AAAAaasdAAAAA", DIGEST_LEN);
  test_memeq(smartlist_get(sl, 2), "AAAAAAAAAAAAAAAAAAAA", DIGEST_LEN);
  test_eq(3, smartlist_len(sl));


  smartlist_uniq_digests(sl);
  test_eq(2, smartlist_len(sl));
  test_memeq(smartlist_get(sl, 0), "\00090AAB2AAAAaasdAAAAA", DIGEST_LEN);
  test_memeq(smartlist_get(sl, 1), "AAAAAAAAAAAAAAAAAAAA", DIGEST_LEN);

 done:
  SMARTLIST_FOREACH(sl, char *, cp, tor_free(cp));
  smartlist_free(sl);
}
