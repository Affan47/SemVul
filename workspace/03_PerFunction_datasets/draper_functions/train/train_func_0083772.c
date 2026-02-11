up_connections_changed(property_t prop)
{
	g_assert(PROP_UP_CONNECTIONS == prop);

    if (GNET_PROPERTY(up_connections) > GNET_PROPERTY(max_connections)) {
        gnet_prop_set_guint32_val(PROP_MAX_CONNECTIONS,
			GNET_PROPERTY(up_connections));
	}
    return FALSE;
}
