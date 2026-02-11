gimmix_update_shuffle (void)
{
	if (is_gimmix_shuffle (gmo))
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(shuffle_toggle_button), TRUE);
	else
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(shuffle_toggle_button), FALSE);

	return;
}
