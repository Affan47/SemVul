privacy_inhibit_encrypt_warning(const gchar *id, gboolean inhibit)
{
	PrivacySystem *system;

	cm_return_if_fail(id != NULL);

	system = privacy_get_system(id);
	if (system == NULL)
		return;
	if (!system->can_encrypt)
		return;
	if (system->inhibit_encrypt_warning == NULL)
		return;

	system->inhibit_encrypt_warning(inhibit);
}
