gsd_wacom_tablet_button_copy (GsdWacomTabletButton *button)
{
	GsdWacomTabletButton *ret;

	g_return_val_if_fail (button != NULL, NULL);

	ret = g_new0 (GsdWacomTabletButton, 1);
	ret->name = g_strdup (button->name);
	if (button->settings != NULL)
		ret->settings = g_object_ref (button->settings);
	ret->id = button->id;
	ret->type = button->type;
	ret->group_id = button->group_id;

	return ret;
}
