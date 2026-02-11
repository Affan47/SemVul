text_index_name_add_word (CamelIndexName *idn,
                          const gchar *word)
{
	CamelTextIndexNamePrivate *p = ((CamelTextIndexName *) idn)->priv;

	if (g_hash_table_lookup (idn->words, word) == NULL) {
		gchar *w = camel_mempool_strdup (p->pool, word);

		g_hash_table_insert (idn->words, w, w);
	}
}
