glade_get_displayable_value (GType          type,
			     const gchar   *value)
{
	ValueTab  *tab;
	gpointer   klass;
	GList     *values, *tab_iter;
	gchar     *displayable = NULL;

	g_return_val_if_fail (value && value[0], NULL);

	if (!values_hash)
		return NULL;

	klass = g_type_class_ref (type);

	g_return_val_if_fail  (klass != NULL, NULL);

	if ((values   = g_hash_table_lookup (values_hash, klass)) != NULL &&
	    (tab_iter = g_list_find_custom  (values, value, (GCompareFunc)find_by_value)) != NULL)
	{
		tab = tab_iter->data;
		displayable = tab->string;
	}
	g_type_class_unref (klass);

	return displayable;
}
