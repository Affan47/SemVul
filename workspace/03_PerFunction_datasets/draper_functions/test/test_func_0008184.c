midgard_core_object_prop_parent_is_set(MidgardObject *object)
{
	g_assert(object != NULL);

	MidgardObjectClass *klass = MIDGARD_OBJECT_GET_CLASS(object);
	GType ptype = midgard_core_object_get_property_parent_type(klass);

	if (ptype == 0)
		return FALSE;

	GValue gval = {0, };
	g_value_init(&gval, ptype);
	const gchar *prop = MGD_DBCLASS_PROPERTY_PARENT (klass);

	g_object_get_property(G_OBJECT(object), prop, &gval);

	if (ptype == G_TYPE_UINT) {

		guint i = g_value_get_uint(&gval);
		g_value_unset (&gval);
		if (i == 0)
			return FALSE;

		return TRUE;

	} else if (ptype == G_TYPE_STRING) {

		const gchar *s = g_value_get_string(&gval);
		gboolean _rv = TRUE;

		if (s == NULL || *s == '\0')
			_rv = FALSE;

		g_value_unset (&gval);

		return _rv;
	}

	if (G_IS_VALUE (&gval))
		g_value_unset (&gval);

	return FALSE;
}
