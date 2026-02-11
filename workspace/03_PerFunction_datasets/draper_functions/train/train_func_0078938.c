dom_element_set_attribute (DomElement *self,
			   const char *name,
			   const char *value)
{
	g_return_if_fail (DOM_IS_ELEMENT (self));
	g_return_if_fail (name != NULL);

	if (value == NULL)
		g_hash_table_remove (self->attributes, name);
	else
		g_hash_table_insert (self->attributes, g_strdup (name), g_strdup (value));
}
