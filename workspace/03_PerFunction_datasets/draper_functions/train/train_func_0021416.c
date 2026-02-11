urf_killswitch_new (UrfEnumType type)
{
	UrfKillswitch *killswitch;

	if (type == URF_ENUM_TYPE_ALL)
		return NULL;

	if (urf_killswitch_object[type] != NULL) {
		g_object_ref (urf_killswitch_object[type]);
	} else {
		killswitch = URF_KILLSWITCH (g_object_new (URF_TYPE_KILLSWITCH, NULL));
		killswitch->priv->type = type;
		if (urf_killswitch_startup (killswitch) == FALSE)
			return NULL;
		urf_killswitch_object[type] = (gpointer)killswitch;
		g_object_add_weak_pointer (urf_killswitch_object[type], &urf_killswitch_object[type]);
	}

	return URF_KILLSWITCH (urf_killswitch_object[type]);
}
