print_metadata_string (RBMetaData *md, RBMetaDataField field, const char *name)
{
	GValue v = {0,};
	if (rb_metadata_get (md, field, &v)) {
		char *s;

		s = g_strdup_value_contents (&v);
		printf ("%s: %s\n", name, s);
		g_free (s);
		g_value_unset (&v);
	}
}
