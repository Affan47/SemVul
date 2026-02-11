ccss_block_dump (ccss_block_t const *self)
{
	GHashTableIter		 iter;
	GQuark			 property_id;
	ccss_property_t const	*property;
	char			*strval;

	g_hash_table_iter_init (&iter, self->properties);
	while (g_hash_table_iter_next (&iter, (gpointer *) &property_id, (gpointer *) &property))  {

		strval = NULL;
		if (CCSS_PROPERTY_STATE_NONE == property->state ||
		    CCSS_PROPERTY_STATE_INHERIT == property->state) {

			strval = g_strdup (ccss_property_state_serialize (property->state));

		} else if (property->vtable &&
			   property->vtable->convert) {

			property->vtable->convert (property,
						   CCSS_PROPERTY_TYPE_STRING,
						   &strval);
		}

		if (NULL == strval)
			strval = g_strdup ("<unknown>");

		printf ("\t%s: %s;\n",
			g_quark_to_string (property_id),
			strval);
		g_free (strval);
	}
}
