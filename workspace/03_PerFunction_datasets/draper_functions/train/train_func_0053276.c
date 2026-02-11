signed_desc_digest_is_recognized(signed_descriptor_t *desc)
{
  const routerstatus_t *rs;
  networkstatus_t *consensus = networkstatus_get_latest_consensus();
  int caches = directory_caches_dir_info(get_options());
  const smartlist_t *networkstatus_v2_list = networkstatus_get_v2_list();

  if (consensus) {
    rs = networkstatus_vote_find_entry(consensus, desc->identity_digest);
    if (rs && tor_memeq(rs->descriptor_digest,
                      desc->signed_descriptor_digest, DIGEST_LEN))
      return 1;
  }
  if (caches && networkstatus_v2_list) {
    SMARTLIST_FOREACH(networkstatus_v2_list, networkstatus_v2_t *, ns,
    {
      if (!(rs = networkstatus_v2_find_entry(ns, desc->identity_digest)))
        continue;
      if (tor_memeq(rs->descriptor_digest,
                  desc->signed_descriptor_digest, DIGEST_LEN))
        return 1;
    });
  }
  return 0;
}
