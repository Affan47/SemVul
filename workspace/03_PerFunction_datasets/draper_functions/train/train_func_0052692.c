data_insert(const struct fakestat *buf,
			const uint32_t remote)
{
  data_node_t *n, *last = NULL;

  for (n = data_hash_table[data_hash_val(buf)]; n; last = n, n = n->next)
    if (fakestat_equal(&n->buf, buf) && n->remote == remote)
      break;

  if (n == NULL) {
    n = calloc(1, sizeof (data_node_t));

    if (last)
      last->next = n;
    else
      data_hash_table[data_hash_val(buf)] = n;
  }

  memcpy(&n->buf, buf, sizeof (struct fakestat));
  n->xattr = NULL;
  n->remote = (uint32_t) remote;
}
