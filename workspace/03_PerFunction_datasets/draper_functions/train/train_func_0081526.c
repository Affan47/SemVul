midgard_object_get_parameter(MidgardObject *self,
		const gchar *domain, const gchar *name)
{
	g_assert(self);

	if(!__is_guid_valid(self))
		return NULL;

	GValue *ret_value;
	MidgardCollector *domain_collector =
		__get_parameters_collector(self, domain);

	if(domain_collector == NULL){

		MidgardCollector *mc =
			__create_domain_collector(MGD_OBJECT_CNC (self), domain);


		GValue guid_value = {0, };
		g_value_init(&guid_value, G_TYPE_STRING);
		g_value_set_string(&guid_value, MGD_OBJECT_GUID (self));

		midgard_collector_add_constraint(mc,
				"parentguid", "=", &guid_value);
		g_value_unset(&guid_value);

		midgard_collector_execute(mc);


		self->priv->parameters =
			g_slist_prepend(self->priv->parameters, mc);

		ret_value =
			midgard_collector_get_subkey(mc, name, "value");

		__register_domain_collector(self, domain, mc);

		return (const GValue*)ret_value;

	} else {

		ret_value =
			midgard_collector_get_subkey(
					domain_collector, name, "value");
		return (const GValue *)ret_value;
	}

	return NULL;
}
