utf8proc_decompose(
  const uint8_t *str, ssize_t slen,
  int32_t *buffer, ssize_t bufsize, int options
) {

  ssize_t wpos = 0;
  if ((options & UTF8PROC_COMPOSE) && (options & UTF8PROC_DECOMPOSE))
    return UTF8PROC_ERROR_INVALIDOPTS;
  if ((options & UTF8PROC_STRIPMARK) &&
      !(options & UTF8PROC_COMPOSE) && !(options & UTF8PROC_DECOMPOSE))
    return UTF8PROC_ERROR_INVALIDOPTS;
  {
    int32_t uc;
    ssize_t rpos = 0;
    ssize_t decomp_result;
    int boundclass = UTF8PROC_BOUNDCLASS_START;
    while (1) {
      if (options & UTF8PROC_NULLTERM) {
        rpos += utf8proc_iterate(str + rpos, -1, &uc);


        if (uc < 0) return UTF8PROC_ERROR_INVALIDUTF8;
        if (rpos < 0) return UTF8PROC_ERROR_OVERFLOW;
        if (uc == 0) break;
      } else {
        if (rpos >= slen) break;
        rpos += utf8proc_iterate(str + rpos, slen - rpos, &uc);
        if (uc < 0) return UTF8PROC_ERROR_INVALIDUTF8;
      }
      decomp_result = utf8proc_decompose_char(
        uc, buffer + wpos, (bufsize > wpos) ? (bufsize - wpos) : 0, options,
        &boundclass
      );
      if (decomp_result < 0) return decomp_result;
      wpos += decomp_result;

      if (wpos < 0 || wpos > SSIZE_MAX/sizeof(int32_t)/2)
        return UTF8PROC_ERROR_OVERFLOW;
    }
  }
  if ((options & (UTF8PROC_COMPOSE|UTF8PROC_DECOMPOSE)) && bufsize >= wpos) {
    ssize_t pos = 0;
    while (pos < wpos-1) {
      int32_t uc1, uc2;
      const utf8proc_property_t *property1, *property2;
      uc1 = buffer[pos];
      uc2 = buffer[pos+1];
      property1 = utf8proc_get_property(uc1);
      property2 = utf8proc_get_property(uc2);
      if (property1->combining_class > property2->combining_class &&
          property2->combining_class > 0) {
        buffer[pos] = uc2;
        buffer[pos+1] = uc1;
        if (pos > 0) pos--; else pos++;
      } else {
        pos++;
      }
    }
  }
  return wpos;
}
