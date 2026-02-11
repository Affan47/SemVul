midgard_core_object_parameters_purge(
		MidgardConnection *mgd, const gchar *class_name,
		const gchar *guid, guint n_params, const GParameter *parameters)
{
	g_assert(mgd != NULL);
	g_assert(class_name != NULL);
	g_assert(guid != NULL);

	GObject **objects = __fetch_parameter_objects(
			mgd, class_name, guid, n_params, parameters);


	if(!objects)
		return FALSE;

	gboolean rv = FALSE;
	guint i = 0;

	while (objects[i] != NULL ) {

		if(midgard_object_purge(MIDGARD_OBJECT(objects[i]), FALSE))
			rv = TRUE;

		g_object_unref(objects[i]);
		i++;
	}

	g_free(objects);
	return rv;
}
