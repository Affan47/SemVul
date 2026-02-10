mmap_string_insert_len (MMAPString     *string,
			size_t       pos,
			const char *val,
			size_t       len)
{
  if (mmap_string_maybe_expand (string, len) == NULL)
    return NULL;

  if (pos < string->len)
    memmove (string->str + pos + len, string->str + pos, string->len - pos);


  memmove (string->str + pos, val, len);

  string->len += len;

  string->str[string->len] = 0;

  return string;
}
