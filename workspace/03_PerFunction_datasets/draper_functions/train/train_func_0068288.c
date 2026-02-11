gda_column_set_name (GdaColumn *column, const gchar *name)
{
	gchar *old_name = NULL;
	GValue *value = NULL;

	g_return_if_fail (GDA_IS_COLUMN (column));

	old_name = (gchar *) gda_column_get_name (column);
	if (old_name)
		old_name = g_strdup (old_name);

	if (name)
		g_value_set_string ((value = gda_value_new (G_TYPE_STRING)), name);
	gda_column_set_attribute_static (column, GDA_ATTRIBUTE_NAME, value);
	if (value)
		gda_value_free (value);

	g_signal_emit (G_OBJECT (column),
		       gda_column_signals[NAME_CHANGED],
		       0, old_name);

	g_free (old_name);
}
