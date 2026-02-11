vote_routerstatus_free(vote_routerstatus_t *rs)
{
  vote_microdesc_hash_t *h, *next;
  if (!rs)
    return;
  tor_free(rs->version);
  tor_free(rs->status.exitsummary);
  for (h = rs->microdesc; h; h = next) {
    tor_free(h->microdesc_hash_line);
    next = h->next;
    tor_free(h);
  }
  tor_free(rs);
}
