find_attribute (const gchar  *name,
		const gchar **attribute_names,
		const gchar **attribute_values)
{
  gint i;

  for (i = 0; attribute_names[i] != NULL; i++)
    if (strcmp (attribute_names[i], name) == 0)
      return attribute_values[i];

  return 0;
}
