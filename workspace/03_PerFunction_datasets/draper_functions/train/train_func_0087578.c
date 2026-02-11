bstr_catBStr(bstr_t to, bstr_t from)
{
  bstr_t ret;
  size_t tolen,
         fromlen;
  if (from == NULL) return to;
  if (to == NULL)   return bstr_dup(from);
  tolen   = bstr_len(to);
  fromlen = bstr_len(from);

  ret = _bstr_resize(to, tolen + fromlen);
  if (ret == NULL) return NULL;
  memcpy((char *)ret + tolen, from, fromlen * sizeof(char));
  ((char *)ret)[tolen + fromlen] = '\0';

  return ret;
}
