cc_wacom_panel_switch_to_panel (CcWacomPanel *self,
				const char   *panel)
{
	CcShell *shell;
	GError *error = NULL;

	g_return_if_fail (self);

	shell = cc_panel_get_shell (CC_PANEL (self));
	if (cc_shell_set_active_panel_from_id (shell, panel, NULL, &error) == FALSE)
	{
		g_warning ("Failed to activate '%s' panel: %s", panel, error->message);
		g_error_free (error);
	}
}
