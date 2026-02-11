get_gtk_doc (const char *id)
{
	char *val;

	if(!gtk_doc_hash)
		return NULL;

	val = g_hash_table_lookup(gtk_doc_hash, id);
	if(val)
		return g_strdup_printf("/**\n * %s_%s:\n%s **/\n",
				       funcbase, id, val);
	val = g_hash_table_lookup(gtk_doc_hash, id);
	if(val)
		return g_strdup_printf("/**\n * %s_%s:\n%s **/\n",
				       funcbase, id, val);
	return NULL;
}
