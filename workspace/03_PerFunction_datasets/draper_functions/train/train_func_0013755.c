unescape(const char * src, size_t src_len, char * dst)
{
  size_t dst_len;

  dst_len = 0;

  while (src_len)
  {
    if (src_len >= 3 &&
        src[0] == '%' &&
        ((src[1] >= '0' && src[1] <= '9') ||
         (src[1] >= 'A' && src[1] <= 'F')) &&
        ((src[2] >= '0' && src[2] <= '9') ||
         (src[2] >= 'A' && src[2] <= 'F')))
    {
      *dst = (HEX_TO_INT(src[1]) << 4) | HEX_TO_INT(src[2]);

      src_len -= 3;
      src += 3;
    }
    else
    {
      *dst = *src;
      src_len--;
      src++;
    }
    dst++;
    dst_len++;
  }

  return dst_len;
}
