md5_update_data (md5_t *ctx, const void *buf, unsigned int buflen)
{

  if (ctx == NULL || ctx->magic != MD5_MAGIC || buf == NULL)
    {
      errno = EINVAL;
      return (-1);
    }

  if (buflen == 0)
    return (0);

  if ((Mlen + buflen) >= MD5_BLOCK_LENGTH)
    {
      unsigned int bufcount;

      bufcount = (MD5_BLOCK_LENGTH - Mlen);
      memcpy (M + Mlen, buf, bufcount);
      _md5_update_digest (ctx);
      _md5_update_count (ctx, bufcount);

      while ((buflen - bufcount) >= MD5_BLOCK_LENGTH)
        {
          memcpy (M, buf + bufcount, MD5_BLOCK_LENGTH);
          bufcount += MD5_BLOCK_LENGTH;
          _md5_update_digest (ctx);
          _md5_update_count (ctx, MD5_BLOCK_LENGTH);
        }

      Mlen = buflen - bufcount;
      if (Mlen > 0)
        {
          memcpy (M, buf + bufcount, Mlen);
          _md5_update_count (ctx, Mlen);
        }
    }
  else
    {

      memcpy (M + Mlen, buf, buflen);
      Mlen += buflen;
      _md5_update_count (ctx, buflen);
    }

  return (buflen);
}
