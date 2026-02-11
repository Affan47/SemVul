gitg_revision_panel_default_init (GitgRevisionPanelInterface *iface)
{
	static gboolean initialized = FALSE;

	iface->initialize = gitg_revision_panel_initialize_default;
	iface->get_id = gitg_revision_panel_get_id_default;
	iface->get_label = gitg_revision_panel_get_label_default;
	iface->get_panel = gitg_revision_panel_get_panel_default;
	iface->update = gitg_revision_panel_update_default;

	if (!initialized)
	{
		initialized = TRUE;
	}
}
