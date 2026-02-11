glade_register_translated_value (GType          type,
				 const gchar   *value,
				 const gchar   *string)
{
	ValueTab *tab;
	gpointer  klass;
	GList    *values;

	g_return_if_fail (value && value[0]);
	g_return_if_fail (string && string[0]);
	klass = g_type_class_ref (type);
	g_return_if_fail (klass != NULL);

	if (!values_hash)
		values_hash = g_hash_table_new (NULL, NULL);

	tab = g_new0 (ValueTab, 1);
	tab->value  = g_strdup (value);
	tab->string = g_strdup (string);

	if ((values =
	     g_hash_table_lookup (values_hash, klass)) != NULL)
	{
		if (!g_list_find_custom (values, tab->value, (GCompareFunc)find_by_value))
			values = g_list_append (values, tab);
		else
		{
			g_warning ("Already registered displayable value %s for %s (type %s)",
				   tab->string, tab->value, g_type_name (type));
			g_free (tab->string);
			g_free (tab->value);
			g_free (tab);
		}
	}
	else
	{
		values = g_list_append (NULL, tab);
		g_hash_table_insert (values_hash, klass, values);
	}
	g_type_class_unref (klass);
}
