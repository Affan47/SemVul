ganv_port_get_property(GObject*    object,
                       guint       prop_id,
                       GValue*     value,
                       GParamSpec* pspec)
{
	g_return_if_fail(object != NULL);
	g_return_if_fail(GANV_IS_PORT(object));

	GanvPort* port = GANV_PORT(object);

	switch (prop_id) {
		GET_CASE(IS_INPUT, boolean, port->impl->is_input);
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}
