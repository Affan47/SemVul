midgard_core_object_parameter_query_builder(
		MidgardConnection *mgd, const gchar *class_name, const gchar *guid)
{
	g_assert(mgd != NULL);
	g_assert(class_name != NULL);
	g_assert(guid != NULL);

	MidgardQueryBuilder *builder =
		midgard_query_builder_new(mgd, class_name);


	if(!builder)
		return NULL;

	GValue gval = {0, };
	g_value_init(&gval, G_TYPE_STRING);
	g_value_set_string(&gval, guid);

	if(!midgard_query_builder_add_constraint(builder, "parentguid", "=", &gval)) {

		g_value_unset(&gval);
		g_object_unref(builder);
		return NULL;
	}

	g_value_unset(&gval);

	return builder;
}
