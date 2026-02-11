gmp_snprintf_memory (struct gmp_snprintf_t *d, const char *str, size_t len)
{
  size_t n;

  ASSERT (d->size >= 0);

  if (d->size > 1)
    {
      n = MIN (d->size-1, len);
      memcpy (d->buf, str, n);
      d->buf += n;
      d->size -= n;
    }
  return len;
}
