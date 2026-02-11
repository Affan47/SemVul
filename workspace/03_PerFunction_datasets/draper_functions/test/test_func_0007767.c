eina_strbuf_common_append_n(size_t csize,
                            Eina_Strbuf *buf,
                            const void *str,
                            size_t len,
                            size_t maxlen)
{
   EINA_SAFETY_ON_NULL_RETURN_VAL(str, EINA_FALSE);

   if (len > maxlen) len = maxlen;
   if (EINA_UNLIKELY(!_eina_strbuf_common_grow(csize, buf, buf->len + len)))
      return EINA_FALSE;
   memcpy(((unsigned char *)(buf->buf)) + (buf->len * csize), str,
          len * csize);
   buf->len += len;
   memset(((unsigned char *)(buf->buf)) + (buf->len * csize), 0, csize);
   return EINA_TRUE;
}
