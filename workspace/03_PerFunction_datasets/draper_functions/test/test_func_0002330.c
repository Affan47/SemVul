dotlock_destroy_unix (dotlock_t h)
{
  if (h->locked && h->lockname)
    unlink (h->lockname);
  if (h->tname && !h->use_o_excl)
    unlink (h->tname);
  jnlib_free (h->tname);
}
