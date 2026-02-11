directory_get_consensus_url(int supports_conditional_consensus,
                            const char *resource)
{
  char *url = NULL;
  const char *hyphen, *flavor;
  if (resource==NULL || strcmp(resource, "ns")==0) {
    flavor = "";
    hyphen = "";
  } else {
    flavor = resource;
    hyphen = "-";
  }

  if (supports_conditional_consensus) {
    char *authority_id_list;
    smartlist_t *authority_digests = smartlist_new();

    SMARTLIST_FOREACH(router_get_trusted_dir_servers(),
                      trusted_dir_server_t *, ds,
      {
        char *hex;
        if (!(ds->type & V3_DIRINFO))
          continue;

        hex = tor_malloc(2*CONDITIONAL_CONSENSUS_FPR_LEN+1);
        base16_encode(hex, 2*CONDITIONAL_CONSENSUS_FPR_LEN+1,
                      ds->v3_identity_digest, CONDITIONAL_CONSENSUS_FPR_LEN);
        smartlist_add(authority_digests, hex);
      });
    smartlist_sort(authority_digests, _compare_strs);
    authority_id_list = smartlist_join_strings(authority_digests,
                                               "+", 0, NULL);

    tor_asprintf(&url, "/tor/status-vote/current/consensus%s%s/%s.z",
                 hyphen, flavor, authority_id_list);

    SMARTLIST_FOREACH(authority_digests, char *, cp, tor_free(cp));
    smartlist_free(authority_digests);
    tor_free(authority_id_list);
  } else {
    tor_asprintf(&url, "/tor/status-vote/current/consensus%s%s.z",
                 hyphen, flavor);
  }
  return url;
}
