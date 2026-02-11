hash_string_insert_prefix (Hash_table **table, char const *string, size_t len,
			   const char **return_prefix)
{
  Hash_table *t = *table;
  char *s;
  char *e;

  if (len)
    {
      s = xmalloc (len + 1);
      memcpy (s, string, len);
      s[len] = 0;
    }
  else
    s = xstrdup (string);

  if (! ((t
	  || (*table = t = hash_initialize (0, 0, hash_string_hasher,
					    hash_string_compare, 0)))
	 && (e = hash_insert (t, s))))
    xalloc_die ();

  if (e == s)
    {
      if (return_prefix)
	*return_prefix = s;
      return 1;
    }
  else
    {
      free (s);
      return 0;
    }
}
