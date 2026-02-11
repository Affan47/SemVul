iso9660_strncpy_pad(char dst[], const char src[], size_t len,
                    enum strncpy_pad_check _check)
{
  size_t rlen;

  cdio_assert (dst != NULL);
  cdio_assert (src != NULL);
  cdio_assert (len > 0);

  switch (_check)
    {
      int idx;
    case ISO9660_NOCHECK:
      break;

    case ISO9660_7BIT:
      for (idx = 0; src[idx]; idx++)
        if ((int8_t) src[idx] < 0)
          {
            cdio_warn ("string '%s' fails 7bit constraint (pos = %d)",
                      src, idx);
            break;
          }
      break;

    case ISO9660_ACHARS:
      for (idx = 0; src[idx]; idx++)
        if (!iso9660_is_achar (src[idx]))
          {
            cdio_warn ("string '%s' fails a-character constraint (pos = %d)",
                      src, idx);
            break;
          }
      break;

    case ISO9660_DCHARS:
      for (idx = 0; src[idx]; idx++)
        if (!iso9660_is_dchar (src[idx]))
          {
            cdio_warn ("string '%s' fails d-character constraint (pos = %d)",
                      src, idx);
            break;
          }
      break;

    default:
      cdio_assert_not_reached ();
      break;
    }

  rlen = strlen (src);

  if (rlen > len)
    cdio_warn ("string '%s' is getting truncated to %d characters",
              src, (unsigned int) len);

  strncpy (dst, src, len);
  if (rlen < len)
    memset(dst+rlen, ' ', len-rlen);
  return dst;
}
