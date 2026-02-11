_cdk_subpkt_get_array (cdk_subpkt_t s, int count, size_t * r_nbytes)
{
  cdk_subpkt_t list;
  byte *buf;
  size_t n, nbytes;

  if (!s)
    {
      if (r_nbytes)
        *r_nbytes = 0;
      return NULL;
    }

  for (n = 0, list = s; list; list = list->next)
    {
      n++;
      n += list->size;
      if (list->size < 192)
        n++;
      else if (list->size < 8384)
        n += 2;
      else
        n += 5;
    }
  buf = cdk_calloc (1, n + 1);
  if (!buf)
    return NULL;

  n = 0;
  for (list = s; list; list = list->next)
    {
      nbytes = 1 + list->size;
      if (nbytes < 192)
        buf[n++] = nbytes;
      else if (nbytes < 8384)
        {
          nbytes -= 192;
          buf[n++] = nbytes / 256 + 192;
          buf[n++] = nbytes & 0xff;
        }
      else
        {
          buf[n++] = 0xFF;
          buf[n++] = nbytes >> 24;
          buf[n++] = nbytes >> 16;
          buf[n++] = nbytes >> 8;
          buf[n++] = nbytes;
        }

      buf[n++] = list->type;
      memcpy (buf + n, list->d, list->size);
      n += list->size;
    }

  if (count)
    {
      cdk_free (buf);
      buf = NULL;
    }
  if (r_nbytes)
    *r_nbytes = n;
  return buf;
}
