gitg_activatable_default_init (GitgActivatableInterface *iface)
{
	static gboolean initialized = FALSE;

	iface->get_id = gitg_activatable_get_id_default;
	iface->activate = gitg_activatable_activate_default;

	if (!initialized)
	{
		initialized = TRUE;
	}
}
