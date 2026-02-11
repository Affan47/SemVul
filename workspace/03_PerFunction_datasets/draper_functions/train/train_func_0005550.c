attr_string (str, len)
     const char *str;
     int len;
{
  struct attr_hash *h;
  int hashcode;
  int i;
  char *new_str;


  hashcode = (len + 1) * 613 + (unsigned) str[0];
  for (i = 1; i <= len; i += 2)
    hashcode = ((hashcode * 613) + (unsigned) str[i]);
  if (hashcode < 0)
    hashcode = -hashcode;


  for (h = attr_hash_table[hashcode % RTL_HASH_SIZE]; h; h = h->next)
    if (h->hashcode == -hashcode && h->u.str[0] == str[0]
	&& !strncmp (h->u.str, str, len))
      return h->u.str;


  new_str = (char *) obstack_alloc (hash_obstack, len + 1);
  memcpy (new_str, str, len);
  new_str[len] = '\0';
  attr_hash_add_string (hashcode, new_str);

  return new_str;
}
