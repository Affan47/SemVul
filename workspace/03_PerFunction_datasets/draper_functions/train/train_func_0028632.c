unregister_identifier (GkmSecretObjectClass *klass, gchar *identifier)
{
	g_assert (klass);
	g_assert (identifier);

	if (klass->identifiers)
		g_hash_table_remove (klass->identifiers, identifier);
	g_free (identifier);
}
