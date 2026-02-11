client_likes_consensus(networkstatus_t *v, const char *want_url)
{
  smartlist_t *want_authorities = smartlist_new();
  int need_at_least;
  int have = 0;

  dir_split_resource_into_fingerprints(want_url, want_authorities, NULL, 0);
  need_at_least = smartlist_len(want_authorities)/2+1;
  SMARTLIST_FOREACH_BEGIN(want_authorities, const char *, d) {
    char want_digest[DIGEST_LEN];
    size_t want_len = strlen(d)/2;
    if (want_len > DIGEST_LEN)
      want_len = DIGEST_LEN;

    if (base16_decode(want_digest, DIGEST_LEN, d, want_len*2) < 0) {
      log_fn(LOG_PROTOCOL_WARN, LD_DIR,
             "Failed to decode requested authority digest %s.", d);
      continue;
    };

    SMARTLIST_FOREACH_BEGIN(v->voters, networkstatus_voter_info_t *, vi) {
      if (smartlist_len(vi->sigs) &&
          tor_memeq(vi->identity_digest, want_digest, want_len)) {
        have++;
        break;
      };
    } SMARTLIST_FOREACH_END(vi);


    if (have >= need_at_least)
      break;
  } SMARTLIST_FOREACH_END(d);

  SMARTLIST_FOREACH(want_authorities, char *, d, tor_free(d));
  smartlist_free(want_authorities);
  return (have >= need_at_least);
}
