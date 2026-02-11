privacy_mimeinfo_check_signature(MimeInfo *mimeinfo)
{
	PrivacySystem *system;

	cm_return_val_if_fail(mimeinfo != NULL, -1);

	if (mimeinfo->privacy == NULL)
		privacy_mimeinfo_is_signed(mimeinfo);

	if (mimeinfo->privacy == NULL)
		return -1;

	system = privacy_data_get_system(mimeinfo->privacy);
	if (system == NULL)
		return -1;

	if (system->check_signature == NULL)
		return -1;

	return system->check_signature(mimeinfo);
}
