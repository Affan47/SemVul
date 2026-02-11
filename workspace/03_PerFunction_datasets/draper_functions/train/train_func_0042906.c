ay_activity_bar_add(const char *label,
		activity_bar_cancel_callback cancel_callback, void *userdata)
{
	ay_activity_bar_pack *abp =
		new ay_activity_bar_pack(label, cancel_callback, userdata, 0, TRUE);

	return abp->get_tag();
}
