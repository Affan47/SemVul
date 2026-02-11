connection_visibility_changed (NMSettings *settings,
                               NMSettingsConnection *connection,
                               gpointer user_data)
{
	NMPolicy *policy = user_data;
	NMPolicyPrivate *priv = NM_POLICY_GET_PRIVATE (policy);

	if (nm_settings_connection_is_visible (connection))
		schedule_activate_all (policy);
	else
		_deactivate_if_active (priv->manager, NM_CONNECTION (connection));
}
