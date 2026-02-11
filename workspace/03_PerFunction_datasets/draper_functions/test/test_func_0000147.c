add_hash (guint *hash,
          gchar *s)
{
	if (s)
		*hash ^= g_str_hash(s);
}
