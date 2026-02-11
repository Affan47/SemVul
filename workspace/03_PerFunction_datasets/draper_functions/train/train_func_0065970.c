str_spliceb(str* s, unsigned start, unsigned len,
		const char* r, unsigned rlen)
{
  if (start > s->len || start + len > s->len)
    return 0;
  if (rlen != len) {
    const long diff = rlen - len;
    if (!str_realloc(s, s->len + diff))
      return 0;
    memmove(s->s + start + rlen, s->s + start + len, s->len - start - len + 1);
    s->len += diff;
  }
  memcpy(s->s + start, r, rlen);
  return 1;
}
